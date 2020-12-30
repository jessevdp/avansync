#include "ClientConsole.hpp"

#include <iostream>

namespace avansync::client
{

  ClientConsole& ClientConsole::instance()
  {
    static ClientConsole instance;
    return instance;
  }

  void ClientConsole::write(const std::string& data) const { std::cout << data; }
  void ClientConsole::write_line(const std::string& data) const { write(data + lf); }

  std::string ClientConsole::read_line() const
  {
    std::string line;
    getline(std::cin, line);
    return line;
  }

} // namespace avansync::client