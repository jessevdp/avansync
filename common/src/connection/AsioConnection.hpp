#pragma once

#include "Connection.hpp"

#include <asio.hpp>
#include <memory>

namespace avansync
{

  class AsioConnection : public Connection
  {
  private:
    inline static const char* crlf {"\r\n"};

    bool _closed {false};
    std::unique_ptr<asio::ip::tcp::iostream> _stream;

  public:
    explicit AsioConnection(std::unique_ptr<asio::ip::tcp::iostream> stream);

    void write_line(const std::string& data) const override;
    [[nodiscard]] std::string read_line() const override;

    void close() override;

    [[nodiscard]] bool is_open() const override;
    explicit operator bool() const override;

    std::string local_endpoint_name() const override;
  };

} // namespace avansync
