#include "command/GetCommand.hpp"

#include "Context.hpp"
#include "connection/Connection.hpp"
#include "filesystem/FileBuffer.hpp"
#include "filesystem/Filesystem.hpp"
#include "test-utils/TestFileBuffer.hpp"

#include <catch.hpp>
#include <fakeit.hpp>
#include <string>

using namespace avansync;
using namespace avansync::server;
using namespace avansync::server::command;
using namespace fakeit;

TEST_CASE("GetCommand")
{
  std::string filename {"bar/foo.txt"};
  int filesize {10};
  auto file_buffer = std::make_unique<char[]>(filesize);

  Mock<Filesystem> mock_filesystem;
  When(Method(mock_filesystem, read_file).Using(filename)).AlwaysDo([&filesize, &file_buffer](const auto& arg) {
    return std::make_unique<TestFileBuffer>(filesize, file_buffer.get());
  });

  Mock<Connection> mock_connection;
  When(Method(mock_connection, read_line)).Return(filename);
  Fake(Method(mock_connection, write_line));
  Fake(Method(mock_connection, write_bytes));
  Fake(Method(mock_connection, write_exception));

  Mock<Context> mock_context;
  When(Method(mock_context, connection)).AlwaysReturn(mock_connection.get());
  When(Method(mock_context, filesystem)).AlwaysReturn(mock_filesystem.get());

  GetCommand command;

  WHEN("all is well")
  {
    THEN("the command writes returns the requested file (communicated via connection) to the client")
    {
      command.execute(mock_context.get());

      // Can't verify arguments to connection.write_line and filesystem.read_file they are reference types (const
      // string&) See https://github.com/eranpeer/FakeIt/wiki/Dangers-of-checking-arguments-passed-by-reference
      // The 'filesystem.read_file' case is covered by the fact that its mock doesn't return any file if the
      // correct filename is not used.
      Verify(Method(mock_connection, read_line)).Once();
      Verify(Method(mock_filesystem, read_file)).Once();
      Verify(Method(mock_connection, write_line)).Once();
      Verify(Method(mock_connection, write_bytes).Using(filesize, file_buffer.get())).Once();
    }
  }
  WHEN("filesystem.read_file throws")
  {
    When(Method(mock_filesystem, read_file)).Throw(FilesystemException {"problem"});

    THEN("the command writes the exception to the client")
    {
      command.execute(mock_context.get());

      Verify(Method(mock_connection, read_line)).Once();
      Verify(Method(mock_filesystem, read_file)).Once();
      Verify(Method(mock_connection, write_exception)).Once();

      // Verify that the command doesn't attempt to write the file to the client
      Verify(Method(mock_connection, write_line)).Never();
      Verify(Method(mock_connection, write_bytes)).Never();
    }
  }
}