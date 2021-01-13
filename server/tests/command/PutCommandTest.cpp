#include "command/PutCommand.hpp"

#include "Context.hpp"
#include "connection/Connection.hpp"
#include "filesystem/FileBuffer.hpp"
#include "filesystem/Filesystem.hpp"

#include <catch.hpp>
#include <fakeit.hpp>
#include <string>

using namespace avansync;
using namespace avansync::server;
using namespace avansync::server::command;
using namespace fakeit;

TEST_CASE("PutCommand")
{
  std::string filename {"bar/foo.txt"};
  int filesize {10};

  Mock<Filesystem> mock_filesystem;
  std::string passed_path;
  char* filesystem_passed_buffer {nullptr};
  When(Method(mock_filesystem, overwrite_file)).AlwaysDo([&](const std::string& path, auto& buffer) {
    passed_path = path;
    filesystem_passed_buffer = buffer.data();
  });

  Mock<Connection> mock_connection;
  When(Method(mock_connection, read_line)).Return(filename).Return(std::to_string(filesize));
  Fake(Method(mock_connection, write_line));
  Fake(Method(mock_connection, write_exception));
  Fake(Method(mock_connection, read_bytes));

  Mock<Context> mock_context;
  When(Method(mock_context, connection)).AlwaysReturn(mock_connection.get());
  When(Method(mock_context, filesystem)).AlwaysReturn(mock_filesystem.get());

  PutCommand command;

  SECTION("reads the file name, file size, and file contents from the client")
  {
    command.execute(mock_context.get());

    Verify(Method(mock_connection, read_line)).Twice();
    Verify(Method(mock_connection, read_bytes).Using(filesize, filesystem_passed_buffer)).Once();
    Verify(Method(mock_filesystem, overwrite_file)).Once();

    REQUIRE(passed_path == filename);
  }

  WHEN("filesystem.overwrite_file is successful")
  {
    command.execute(mock_context.get());

    THEN("the command writes 'OK' to the client")
    {
      Verify(Method(mock_connection, write_line)).Once();
      Verify(Method(mock_connection, write_exception)).Never();
      Verify(Method(mock_connection, write_error)).Never();
      Verify(Method(mock_connection, write_bytes)).Never();
    }
  }

  WHEN("filesystem.overwrite_file throws")
  {
    When(Method(mock_filesystem, overwrite_file)).Throw(FilesystemException {"problem"});

    command.execute(mock_context.get());

    THEN("the command writes the exception to the client")
    {
      Verify(Method(mock_connection, write_exception)).Once();
      Verify(Method(mock_connection, write_line)).Never();
      Verify(Method(mock_connection, write_error)).Never();
      Verify(Method(mock_connection, write_bytes)).Never();
    }
  }
}