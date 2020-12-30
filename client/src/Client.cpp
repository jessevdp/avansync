#include "Client.hpp"

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
    if (!handled) { log() << "Error: unknown command: '" << request << "'" << lf; }
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
    std::cout << _connection->read_line() << lf;
  }

  std::string Client::prompt_request() const
  {
    std::cout << prompt;
    std::string request;
    getline(std::cin, request);
    return request;
  }

  //#region Context

  Connection& Client::connection() const { return *_connection; }

  std::basic_ostream<char>& Client::log() const { return std::cout; }
  void Client::log(const std::string& string) const { log() << string; }

  //#endregion

} // namespace avansync::client