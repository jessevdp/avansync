#include "AsioConnection.hpp"

namespace avansync
{
  AsioConnection::AsioConnection(std::unique_ptr<asio::ip::tcp::iostream> stream) : _stream {std::move(stream)} {}

  void AsioConnection::write_line(const std::string& data) const { (*_stream) << data << crlf; }

  void AsioConnection::write_exception(const std::exception& exception) const { write_exception(exception.what()); }

  void AsioConnection::write_exception(const std::string& message) const
  {
    write_line(EXCEPTION_HEADER);
    write_line(message);
  }

  std::string AsioConnection::read_line() const
  {
    std::string line = do_read_line();

    if (line == EXCEPTION_HEADER)
    {
      std::string message = do_read_line();
      throw std::runtime_error {message};
    }

    return line;
  }

  std::string AsioConnection::do_read_line() const
  {
    std::string line;
    getline(*_stream, line);
    line.erase(line.end() - 1); // remove '\r'
    return line;
  }

  void AsioConnection::close()
  {
    _stream->close();
    _closed = true;
  }

  bool AsioConnection::is_open() const { return !_stream->fail() && !_closed; }
  AsioConnection::operator bool() const { return is_open(); }

  std::string AsioConnection::local_endpoint_name() const
  {
    std::stringstream endpoint_name;
    endpoint_name << _stream->socket().local_endpoint();
    return endpoint_name.str();
  }

} // namespace avansync