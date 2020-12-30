#include "Client.hpp"

#include "ClientConsole.hpp"
#include "command/InfoCommand.hpp"
#include "command/QuitCommand.hpp"
#include "connection/AsioConnection.hpp"
#include "handler/CommandRequestHandler.hpp"

#include <asio.hpp>
#include <iostream>

using namespace asio::ip;
using namespace avansync::client::command;
using namespace avansync::handler;

namespace avansync::client
{

  Client::Client() : _handlers {std::make_unique<RequestHandlerChain>()}
  {
    _handlers->add(std::make_unique<CommandRequestHandler>("info", std::make_unique<InfoCommand>()));
    _handlers->add(std::make_unique<CommandRequestHandler>("quit", std::make_unique<QuitCommand>()));
  }

  void Client::connect_to(const std::string& server_address, const std::string& server_port)
  {
    establish_connection(server_address, server_port);
    on_connect();

    while (_connection->is_open())
    {
      auto request = prompt_request();
      handle_request(request);
    }
  }

  void Client::handle_request(const std::string& request)
  {
    bool handled = _handlers->handle(request, *this);
    if (!handled) { console().write_line("Error: unknown command: '" + request + "'"); }
  }

  void Client::establish_connection(const std::string& server_address, const std::string& server_port)
  {
    auto server = std::make_unique<tcp::iostream>(server_address, server_port);
    if (!server) throw std::runtime_error("could not connect to server");
    _connection = std::make_unique<AsioConnection>(std::move(server));
  }

  void Client::on_connect() const
  {
    // Read welcome message from server
    console().write_line(_connection->read_line());
  }

  std::string Client::prompt_request() const
  {
    console().write(prompt);
    return console().read_line();
  }

  //#region Context

  Connection& Client::connection() const { return *_connection; }
  Console& Client::console() const { return ClientConsole::instance(); }

  //#endregion

} // namespace avansync::client