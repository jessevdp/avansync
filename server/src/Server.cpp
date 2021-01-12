#include "Server.hpp"

#include "ServerConsole.hpp"
#include "command/DeleteCommand.hpp"
#include "command/DirectoryListingCommand.hpp"
#include "command/GetCommand.hpp"
#include "command/InfoCommand.hpp"
#include "command/PutCommand.hpp"
#include "command/QuitCommand.hpp"
#include "connection/AsioConnection.hpp"
#include "filesystem/StandardFilesystem.hpp"
#include "handler/CommandRequestHandler.hpp"

#include <algorithm>
#include <iostream>

using namespace avansync::server::command;

using namespace asio::ip;

using namespace avansync::handler;

namespace avansync::server
{

  Server::Server(int port, const std::string& base_dir_path)
      : _server {_io_context, tcp::endpoint(tcp::v4(), port)},
        _handlers {std::make_unique<RequestHandlerChain>()},
        _filesystem {std::make_unique<StandardFilesystem>(base_dir_path)}
  {
    _handlers->add(std::make_unique<CommandRequestHandler>("info", std::make_unique<InfoCommand>()));
    _handlers->add(std::make_unique<CommandRequestHandler>("dir", std::make_unique<DirectoryListingCommand>()));
    _handlers->add(std::make_unique<CommandRequestHandler>("get", std::make_unique<GetCommand>()));
    _handlers->add(std::make_unique<CommandRequestHandler>("put", std::make_unique<PutCommand>()));
    _handlers->add(std::make_unique<CommandRequestHandler>("del", std::make_unique<DeleteCommand>()));
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
  Filesystem& Server::filesystem() const { return *_filesystem; }

  //#endregion

} // namespace avansync::server