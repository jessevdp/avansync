#pragma once

#include "connection/Connection.hpp"

#include <memory>
#include <string>
#include <iosfwd>

namespace avansync::client
{

  class Client
  {
  private:
    inline static const char* prompt {"avansync> "};
    inline static const char* lf {"\n"};

    std::unique_ptr<Connection> _connection {nullptr};

  public:
    void connect_to(const std::string& server_address, const std::string& server_port);

  private:
    void establish_connection(const std::string& server_address, const std::string& server_port);
    void on_connect() const;
    std::string prompt_request() const;
    void handle_request(const std::string& request);
  };

} // namespace avansync::client
