#include "Server.hpp"

#include "command/InfoCommand.hpp"
#include "command/QuitCommand.hpp"
#include "handler/CommandRequestHandler.hpp"

#include <algorithm>
#include <iostream>

using namespace avansync::server::command;
using namespace avansync::server::handler;

namespace avansync::server
{

  Server::Server(int port) :
      _server {_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)},
      _handlers {std::make_unique<RequestHandlerChain>()}
  {
    _handlers->add(std::make_unique<CommandRequestHandler>("info", std::make_unique<InfoCommand>()));
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
        auto request = read_request();
        handle_request(request);
      }
    }
  }

  void Server::accept_client_connection()
  {
    std::cerr << "waiting for client to connect\n";
    _client = std::make_unique<asio::ip::tcp::iostream>();
    _server.accept(_client->socket());
  }

  void Server::on_connect() const
  {
    log() << "client connected from " << _client->socket().local_endpoint() << lf;
    client() << "Welcome to AvanSync server 1.0" << crlf;
  }

  void Server::handle_request(const std::string& request)
  {
    log() << "client says: " << request << lf;

    bool handled = _handlers->handle(request, *this);
    if (!handled) client() << request << crlf; // simply echo the request
  }

  std::string Server::read_request() const
  {
    std::string request;
    getline(*_client, request);
    request.erase(request.end() - 1); // remove '\r'
    return request;
  }

  void Server::stop() { _running = false; }

  //#region Context

  asio::ip::tcp::iostream& Server::client() const { return *_client; }

  void Server::disconnect_current_client() { _connected = false; }

  void Server::log(const std::string& string) const { log() << string; }
  std::basic_ostream<char>& Server::log() const { return std::cerr; }

  //#endregion

} // namespace avansync::server