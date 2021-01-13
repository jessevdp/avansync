#include "command/DeleteCommand.hpp"

#include <catch.hpp>
#include <fakeit.hpp>

using namespace avansync;
using namespace avansync::server;
using namespace avansync::server::command;
using namespace fakeit;

TEST_CASE("DeleteCommand")
{
  std::string path {"foo/bar.txt"};

  Mock<Connection> mock_connection;
  When(Method(mock_connection, read_line)).Return(path);
  Fake(Method(mock_connection, write_line));
  Fake(Method(mock_connection, write_exception));

  Mock<Filesystem> mock_filesystem;
  std::string passed_path;
  When(Method(mock_filesystem, remove)).AlwaysDo([&](const std::string& path) {
    passed_path = path;
  });

  Mock<Context> mock_context;
  When(Method(mock_context, connection)).AlwaysReturn(mock_connection.get());
  When(Method(mock_context, filesystem)).AlwaysReturn(mock_filesystem.get());

  DeleteCommand command;

  SECTION("reads the 'path' from the client")
  {
    command.execute(mock_context.get());

    Verify(Method(mock_connection, read_line)).Once();
    Verify(Method(mock_filesystem, remove)).Once();
    REQUIRE(passed_path == path);
  }

  WHEN("filesystem.remove is successful")
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
  WHEN("filesystem.remove throws")
  {
    When(Method(mock_filesystem, remove)).Throw(FilesystemException {"problem"});

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