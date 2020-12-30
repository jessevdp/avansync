#include "Client.hpp"

#include "connection/AsioConnection.hpp"

#include <asio.hpp>
#include <iostream>

using namespace asio::ip;

namespace avansync::client
{

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
    // TODO: clean up using request handler chain/pipeline and commands

    if (request == "info")
    {
      _connection->write_line("info");
      std::cout << _connection->read_line() << lf;
    }
    else if (request == "quit")
    {
      _connection->write_line("quit");
      std::cout << _connection->read_line() << lf;
      _connection->close();
    }
    else
    {
      std::cout << "Error: unknown command: '" << request << "'" << lf;
    }
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

}