#include "command/DirectoryListingCommand.hpp"

#include "Context.hpp"
#include "connection/Connection.hpp"
#include "filesystem/Filesystem.hpp"
#include "test-utils/TestDirectoryEntry.hpp"

#include <catch.hpp>
#include <fakeit.hpp>
#include <string>
#include <vector>

using namespace avansync;
using namespace avansync::server;
using namespace avansync::server::command;
using namespace fakeit;

TEST_CASE("DirectoryListingCommand")
{
  std::string dir_name {"foo/bar/"};
  int entry_count {6};

  std::string passed_dir_name;
  Mock<Filesystem> mock_filesystem;
  When(Method(mock_filesystem, directory_entries)).AlwaysDo([&](const std::string& dir) {
    passed_dir_name = dir;

    std::vector<std::unique_ptr<DirectoryEntry>> entries;
    entries.reserve(entry_count);
    for (int i = 0; i < entry_count; ++i)
    {
      entries.push_back(std::make_unique<TestDirectoryEntry>());
    }
    return entries;
  });

  Mock<Connection> mock_connection;
  Fake(Method(mock_connection, write_exception));
  When(Method(mock_connection, read_line)).Return(dir_name);
  std::vector<std::string> written_lines;
  When(Method(mock_connection, write_line)).AlwaysDo([&](const std::string& line) { written_lines.push_back(line); });

  Mock<Context> mock_context;
  When(Method(mock_context, connection)).AlwaysReturn(mock_connection.get());
  When(Method(mock_context, filesystem)).AlwaysReturn(mock_filesystem.get());

  DirectoryListingCommand command;

  SECTION("reads the directory path from the client")
  {
    command.execute(mock_context.get());

    Verify(Method(mock_connection, read_line)).Once();
    Verify(Method(mock_filesystem, directory_entries)).Once();

    REQUIRE(passed_dir_name == dir_name);
  }

  WHEN("filesystem.directory_entries is successful")
  {
    command.execute(mock_context.get());

    THEN("the command writes the number of entries + a line per entry to the client")
    {
      Verify(Method(mock_connection, write_line)).Exactly(entry_count + 1);
      REQUIRE(written_lines[0] == std::to_string(entry_count));
    }
  }

  WHEN("filesystem.directory_entries throws")
  {
    When(Method(mock_filesystem, directory_entries)).Throw(FilesystemException {"problem"});

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