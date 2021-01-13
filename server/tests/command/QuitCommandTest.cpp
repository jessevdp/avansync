#include "command/QuitCommand.hpp"

#include <catch.hpp>
#include <fakeit.hpp>

using namespace avansync;
using namespace avansync::server;
using namespace avansync::server::command;
using namespace fakeit;

TEST_CASE("QuitCommand")
{
  Mock<Connection> mock_connection;
  When(Method(mock_connection, local_endpoint_name)).AlwaysReturn("test-endpoint");
  Fake(Method(mock_connection, close));

  Mock<Console> mock_console;
  Fake(Method(mock_console, write_line));

  Mock<Context> mock_context;
  When(Method(mock_context, connection)).AlwaysReturn(mock_connection.get());
  When(Method(mock_context, console)).AlwaysReturn(mock_console.get());

  QuitCommand command;
  command.execute(mock_context.get());

  SECTION("closes the connection") { Verify(Method(mock_connection, close)).Once(); }

  SECTION("does not write anything to the client")
  {
    Verify(Method(mock_connection, write_line)).Never();
    Verify(Method(mock_connection, write_exception)).Never();
    Verify(Method(mock_connection, write_error)).Never();
    Verify(Method(mock_connection, write_bytes)).Never();
  }

  SECTION("logs disconnection to console")
  {
    // Can't verify arguments to console.write_line beacause it is a  reference types (const string&)
    // See https://github.com/eranpeer/FakeIt/wiki/Dangers-of-checking-arguments-passed-by-reference
    Verify(Method(mock_console, write_line)).Once();
  }
}