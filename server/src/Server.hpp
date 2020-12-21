#pragma once

#include <asio.hpp>
#include <iostream>
#include <string>
#include <memory>

namespace avansync::server {

  class Server {
  private:
    inline static const char* lf {"\n"};
    inline static const char* crlf {"\r\n"};

    asio::io_context _io_context;
    asio::ip::tcp::acceptor _server;
    bool _running {false};
    bool _connected {false};

  public:
    explicit Server(int port);
    void start();
    void stop();
    void disconnect_current_client();

  private:
    std::unique_ptr<asio::ip::tcp::iostream> accept_client_connection();
    void on_connect(asio::ip::tcp::iostream& client) const;
    std::string parse_request(asio::ip::tcp::iostream& client) const;
    void handle_request(std::string request, asio::ip::tcp::iostream& client);
  };

}
