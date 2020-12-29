#pragma once

#include "Context.hpp"
#include "handler/RequestHandlerChain.hpp"

#include <asio.hpp>
#include <memory>
#include <string>

namespace avansync::server
{

  class Server : public Context
  {
  private:
    inline static const char* lf {"\n"};

    bool _running {false};

    asio::io_context _io_context;
    asio::ip::tcp::acceptor _server;

    std::unique_ptr<Connection> _client_connection {nullptr};

    std::unique_ptr<handler::RequestHandlerChain> _handlers;

  public:
    explicit Server(int port);
    void start();
    void stop();

    //#region Context

    [[nodiscard]] Connection& connection() const override;

    void log(const std::string& string) const override;
    [[nodiscard]] std::basic_ostream<char>& log() const override;

    //#endregion

  private:
    void accept_client_connection();
    void on_connect() const;

    void handle_request(const std::string& request);
  };

} // namespace avansync::server
