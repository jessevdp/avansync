#include "AsioConnection.hpp"

namespace avansync
{
  AsioConnection::AsioConnection(std::unique_ptr<asio::ip::tcp::iostream> stream) : _stream {std::move(stream)} {}

  void AsioConnection::write_line(const std::string& data) const { (*_stream) << data << crlf; }

  void AsioConnection::write_exception(const std::exception& exception) const { write_exception(exception.what()); }

  void AsioConnection::write_exception(const std::string& message) const { write_line(EXCEPTION_PREFIX + message); }

  std::string AsioConnection::read_line() const
  {
    std::string line;
    getline(*_stream, line);
    line.erase(line.end() - 1); // remove '\r'

    if (is_exception(line))
    {
      std::string message = retrieve_exception_message(line);
      throw std::runtime_error {message};
    }

    return line;
  }

  void AsioConnection::write_bytes(int amount, char* source_buffer) const {
    _stream->write(source_buffer, amount);
  }

  void AsioConnection::read_bytes(int amount, char* destination_buffer) const {
    _stream->read(destination_buffer, amount);
  }

  bool AsioConnection::is_exception(const std::string& line) const { return line.rfind(EXCEPTION_PREFIX, 0) == 0; }

  std::string AsioConnection::retrieve_exception_message(std::string line) const
  {
    if (is_exception(line)) line.erase(0, EXCEPTION_PREFIX.length());
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