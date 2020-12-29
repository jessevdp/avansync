#include <asio.hpp>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <memory>

#include "AsioConnection.hpp"

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
      if (getline(std::cin, request)) {

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
        else if (request == "dir")
        {
          connection.write_line("dir");

          std::cout << "sub-directory: ";
          std::string dir;
          getline(std::cin, dir);

          connection.write_line(dir);

          int entry_count = std::stoi(connection.read_line());
          for (int i = 0; i < entry_count; ++i)
          {
            std::cout << connection.read_line() << lf;
          }
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
