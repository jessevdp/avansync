#include "command/InfoCommand.hpp"

#include <catch.hpp>
#include <fakeit.hpp>

using namespace avansync;
using namespace avansync::server;
using namespace avansync::server::command;
using namespace fakeit;

TEST_CASE("InfoCommand")
{
  Mock<Connection> mock_connection;
  Fake(Method(mock_connection, write_line));

  Mock<Context> mock_context;
  When(Method(mock_context, connection)).AlwaysReturn(mock_connection.get());

  InfoCommand command;

  SECTION("writes a single line of info to the client")
  {
    command.execute(mock_context.get());
    Verify(Method(mock_connection, write_line)).Once();
  }
}