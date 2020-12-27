#pragma once

#include "Context.hpp"
#include "Request.hpp"
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
    inline static const char* crlf {"\r\n"};

    asio::io_context _io_context;
    asio::ip::tcp::acceptor _server;
    bool _running {false};
    bool _connected {false};

    std::unique_ptr<asio::ip::tcp::iostream> _client {nullptr};

    std::unique_ptr<handler::RequestHandlerChain> _handlers;

  public:
    explicit Server(int port);
    void start();
    void stop();

    //#region Context

    [[nodiscard]] asio::ip::tcp::iostream& client() const override;
    void disconnect_current_client() override;

    void log(std::string string) const override;
    [[nodiscard]] std::basic_ostream<char>& log() const override;

    //#endregion

  private:
    void accept_client_connection();
    void on_connect() const;

    [[nodiscard]] std::unique_ptr<Request> read_request() const;
    void handle_request(const Request& request);
  };

} // namespace avansync::server
