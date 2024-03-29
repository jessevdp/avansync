#pragma once

#include <exception>
#include <string>

namespace avansync
{

  class Connection
  {
  public:
    virtual ~Connection() noexcept = default;

    virtual void write_line(const std::string& data) const = 0;
    virtual void write_error(const std::string& message) const = 0;
    virtual void write_exception(const std::exception& exception) const = 0;

    [[nodiscard]] virtual std::string read_line() const = 0;

    virtual void write_bytes(int amount, char* source_buffer) const = 0;
    virtual void read_bytes(int amount, char* destination_buffer) const = 0;

    virtual void close() = 0;

    [[nodiscard]] virtual bool is_open() const = 0;
    /// Returns a boolean indicating weather or not the Connection is still open
    virtual explicit operator bool() const = 0;

    [[nodiscard]] virtual std::string local_endpoint_name() const = 0;
  };

} // namespace avansync
