#include "Server.hpp"

#include "AsioConnection.hpp"
#include "command/DirectoryListingCommand.hpp"
#include "command/InfoCommand.hpp"
#include "command/QuitCommand.hpp"
#include "handler/CommandRequestHandler.hpp"

#include <algorithm>
#include <iostream>

using namespace avansync::server::command;
using namespace avansync::server::handler;
using namespace asio::ip;

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

      _connected = true;
      while (_connected)
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
    log() << "client connected from " << _client_connection->local_endpoint_name() << lf;
    connection().write_line("Welcome to AvanSync server 1.0");
  }

  void Server::handle_request(const std::string& request)
  {
    log() << "client says: " << request << lf;

    bool handled = _handlers->handle(request, *this);
    if (!handled) connection().write_line(request); // simply echo the request
  }

  void Server::stop() { _running = false; }

  //#region Context

  Connection& Server::connection() const { return *_client_connection; }

  void Server::disconnect_current_client() { _connected = false; }

  void Server::log(const std::string& string) const { log() << string; }
  std::basic_ostream<char>& Server::log() const { return std::cerr; }

  std::string Server::base_dir_path() const { return _base_dir_path; }

  //#endregion

} // namespace avansync::server