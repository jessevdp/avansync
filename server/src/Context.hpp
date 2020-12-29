#pragma once

#include "Connection.hpp"

#include <asio.hpp>
#include <iostream>
#include <string>

namespace avansync::server
{

  class Context
  {
  public:
    virtual ~Context() noexcept = default;

    [[nodiscard]] virtual Connection& connection() const = 0;

    virtual void log(const std::string&) const = 0;
    [[nodiscard]] virtual std::basic_ostream<char>& log() const = 0;
  };

} // namespace avansync::server