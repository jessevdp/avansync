#include "command/CreateDirectoryCommand.hpp"

#include <catch.hpp>
#include <fakeit.hpp>

using namespace avansync;
using namespace avansync::server;
using namespace avansync::server::command;
using namespace fakeit;

TEST_CASE("CreateDirectoryCommand")
{
  std::string path {"old-path"};
  std::string dir_name {"new-name"};

  Mock<Connection> mock_connection;
  When(Method(mock_connection, read_line)).Return(path).Return(dir_name);
  Fake(Method(mock_connection, write_line));
  Fake(Method(mock_connection, write_exception));

  Mock<Filesystem> mock_filesystem;
  std::string passed_path;
  std::string passed_name;
  When(Method(mock_filesystem, create_directory)).AlwaysDo([&](const std::string& path, const std::string& name) {
    passed_path = path;
    passed_name = name;
  });

  Mock<Context> mock_context;
  When(Method(mock_context, connection)).AlwaysReturn(mock_connection.get());
  When(Method(mock_context, filesystem)).AlwaysReturn(mock_filesystem.get());

  CreateDirectoryCommand command;

  SECTION("reads the 'path' and 'dir name' from the client")
  {
    command.execute(mock_context.get());

    Verify(Method(mock_connection, read_line)).Twice();
    Verify(Method(mock_filesystem, create_directory)).Once();
    REQUIRE(passed_path == path);
    REQUIRE(passed_name == dir_name);
  }

  WHEN("filesystem.create_directory is successful")
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
  WHEN("filesystem.create_directory throws")
  {
    When(Method(mock_filesystem, create_directory)).Throw(FilesystemException {"problem"});

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