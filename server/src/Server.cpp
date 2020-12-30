#include "Server.hpp"

#include "ServerConsole.hpp"
#include "command/DirectoryListingCommand.hpp"
#include "command/InfoCommand.hpp"
#include "command/QuitCommand.hpp"
#include "connection/AsioConnection.hpp"
#include "handler/CommandRequestHandler.hpp"

#include <algorithm>
#include <iostream>

using namespace avansync::server::command;

using namespace asio::ip;

using namespace avansync::handler;

namespace avansync::server
{

  // TODO: check if base dir even exists on startup?
  Server::Server(int port, std::string base_dir_path) :
      _base_dir_path {std::move(base_dir_path)}, _server {_io_context, tcp::endpoint(tcp::v4(), port)},
      _handlers {std::make_unique<RequestHandlerChain>()}
  {
    _handlers->add(std::make_unique<CommandRequestHandler>("info", std::make_unique<InfoCommand>()));
    _handlers->add(std::make_unique<CommandRequestHandler>("dir", std::make_unique<DirectoryListingCommand>()));
    _handlers->add(std::make_unique<CommandRequestHandler>("quit", std::make_unique<QuitCommand>()));
  }

  void Server::start()
  {
    _running = true;
    while (_running)
    {
      accept_client_connection();
      on_connect();

      while (_client_connection && _client_connection->is_open())
      {
        auto request = connection().read_line();
        handle_request(request);
      }
    }
  }

  void Server::accept_client_connection()
  {
    std::cerr << "waiting for client to connect\n";
    auto client = std::make_unique<tcp::iostream>();
    _server.accept(client->socket());
    _client_connection = std::make_unique<AsioConnection>(std::move(client));
  }

  void Server::on_connect() const
  {
    console().write_line("client connected from " + _client_connection->local_endpoint_name());
    connection().write_line("Welcome to AvanSync server 1.0");
  }

  void Server::handle_request(const std::string& request)
  {
    console().write_line("client says: " + request);

    bool handled = _handlers->handle(request, *this);
    if (!handled) connection().write_line(request); // simply echo the request
  }

  void Server::stop() { _running = false; }

  //#region Context

  Connection& Server::connection() const { return *_client_connection; }
  Console& Server::console() const { return ServerConsole::instance(); }

  std::string Server::base_dir_path() const { return _base_dir_path; }

  //#endregion

} // namespace avansync::server