#pragma once

#include "Context.hpp"
#include "connection/Connection.hpp"
#include "handler/RequestHandlerChain.hpp"

#include <iosfwd>
#include <memory>
#include <string>

namespace avansync::client
{

  class Client : public Context
  {
  private:
    inline static const char* prompt {"avansync> "};
    inline static const char* lf {"\n"};

    std::unique_ptr<Connection> _connection {nullptr};
    std::unique_ptr<handler::RequestHandlerChain> _handlers;

  public:
    Client();

    void connect_to(const std::string& server_address, const std::string& server_port);

    //#region Context

    [[nodiscard]] Connection& connection() const override;

    void log(const std::string& string) const override;
    [[nodiscard]] std::basic_ostream<char>& log() const override;

    //#endregion

  private:
    void establish_connection(const std::string& server_address, const std::string& server_port);
    void on_connect() const;
    [[nodiscard]] std::string prompt_request() const;
    void handle_request(const std::string& request);
  };

} // namespace avansync::client
