#include "connection/AsioConnection.hpp"

#include <asio.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace avansync;

int main()
{
  try
  {
    const char* server_address {"localhost"};
    const char* server_port {"12345"};
    const char* prompt {"avansync> "};
    const char* lf {"\n"};

    auto server = std::make_unique<asio::ip::tcp::iostream>(server_address, server_port);
    if (!server) throw std::runtime_error("could not connect to server");
    AsioConnection connection {std::move(server)};

    std::cout << connection.read_line() << lf;

    while (connection.is_open())
    {
      std::cout << prompt;
      std::string request;
      if (getline(std::cin, request))
      {

        if (request == "info")
        {
          connection.write_line("info");
          std::cout << connection.read_line() << lf;
        }
        else if (request == "quit")
        {
          connection.write_line("quit");
          std::cout << connection.read_line() << lf;
          connection.close();
        }
        else
        {
          std::cout << "Error: unknown command: '" << request << "'" << lf;
        }
      }
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << "client: " << ex.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
