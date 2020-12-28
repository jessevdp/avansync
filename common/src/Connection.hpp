#pragma once

#include <string>

namespace avansync
{

  class Connection
  {
  public:
    virtual ~Connection() noexcept = default;

    virtual void write_line(const std::string& data) const = 0;
    [[nodiscard]] virtual std::string read_line() const = 0;
  };

} // namespace avansync
