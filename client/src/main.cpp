#include "Client.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace avansync::client;

int main()
{
  try
  {
    const char* server_address {"localhost"};
    const char* server_port {"12345"};

    Client client;
    client.connect_to(server_address, server_port);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "client: " << ex.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
