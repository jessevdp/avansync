#include "Server.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace avansync::server;

int main() {
  try {
    const int server_port {12345};
    Server server {server_port};
    server.start();
  } catch (const std::exception& ex) {
    std::cerr << "server: " << ex.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
