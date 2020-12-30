#pragma once

#include "Connection.hpp"

#include <asio.hpp>
#include <memory>

namespace avansync
{

  class AsioConnection : public Connection
  {
  private:
    inline static const std::string EXCEPTION_HEADER = "ERROR";
    inline static const char* crlf {"\r\n"};

    bool _closed {false};
    std::unique_ptr<asio::ip::tcp::iostream> _stream;

  public:
    explicit AsioConnection(std::unique_ptr<asio::ip::tcp::iostream> stream);

    void write_line(const std::string& data) const override;
    void write_exception(const std::string& message) const override;
    void write_exception(const std::exception& exception) const override;

    /**
     * Read a single line of data send from the other side of the connection.
     *
     * @throws std::runtime_error when it encounters an exception send from the other side of the connection. (Indicated
     * by a single line containing the EXCEPTION_HEADER followed by a line containing the error message.)
     *
     * @return the line of data
     */
    [[nodiscard]] std::string read_line() const override;

    void close() override;

    [[nodiscard]] bool is_open() const override;
    explicit operator bool() const override;

    [[nodiscard]] std::string local_endpoint_name() const override;

  private:
    [[nodiscard]] std::string do_read_line() const;
  };

} // namespace avansync
