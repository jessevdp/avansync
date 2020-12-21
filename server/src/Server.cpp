#include "Server.hpp"

namespace avansync::server
{

  Server::Server(int port) : _server {_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)} {}

  void Server::start()
  {
    _running = true;
    while (_running)
    {
      auto client = accept_client_connection();
      on_connect(*client);

      _connected = true;
      while (_connected)
      {
        std::string request = parse_request(*client);
        handle_request(request, *client);
      }
    }
  }

  std::unique_ptr<asio::ip::tcp::iostream> Server::accept_client_connection()
  {
    std::cerr << "waiting for client to connect\n";
    auto client = std::make_unique<asio::ip::tcp::iostream>();
    _server.accept(client->socket());
    return client;
  }

  void Server::on_connect(asio::ip::tcp::iostream& client) const
  {
    std::cerr << "client connected from " << client.socket().local_endpoint() << lf;
    client << "Welcome to AvanSync server 1.0" << crlf;
  }

  void Server::handle_request(std::string& request, asio::ip::tcp::iostream& client)
  {
    std::cerr << "client says: " << request << lf;

    if (request == "quit")
    {
      client << "Bye." << crlf;
      std::cerr << "will disconnect from client " << client.socket().local_endpoint() << lf;
      disconnect_current_client();
    }
    else
    {
      client << request << crlf; // simply echo the request
    }
  }

  std::string Server::parse_request(asio::ip::tcp::iostream& client) const
  {
    std::string request;
    getline(client, request);
    request.erase(request.end() - 1); // remove '\r'
    return request;
  }

  void Server::stop() { _running = false; }

  void Server::disconnect_current_client() { _connected = false; }

} // namespace avansync::server