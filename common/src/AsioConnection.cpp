#include "AsioConnection.hpp"

namespace avansync
{
  AsioConnection::AsioConnection(std::unique_ptr<asio::ip::tcp::iostream> stream) : _stream {std::move(stream)} {}

  void AsioConnection::write_line(const std::string& data) const { (*_stream) << data << crlf; }

  std::string AsioConnection::read_line() const
  {
    std::string line;
    getline(*_stream, line);
    line.erase(line.end() - 1); // remove '\r'
    return line;
  }

} // namespace avansync