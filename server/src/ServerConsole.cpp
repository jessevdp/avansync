#include "ServerConsole.hpp"

#include <iostream>
#include <stdexcept>

namespace avansync::server
{

  ServerConsole& ServerConsole::instance()
  {
    static ServerConsole instance;
    return instance;
  }

  void ServerConsole::write(const std::string& data) const { std::cerr << data; }
  void ServerConsole::write_line(const std::string& data) const { write(data + lf); }

  std::string ServerConsole::read_line() const { throw std::logic_error {"Cannot read data from ServerConsole"}; }

} // namespace avansync::server