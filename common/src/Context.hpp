#pragma once

#include "Console.hpp"
#include "connection/Connection.hpp"
#include "filesystem/Filesystem.hpp"

#include <asio.hpp>
#include <iostream>
#include <string>

namespace avansync
{

  class Context
  {
  public:
    virtual ~Context() noexcept = default;

    [[nodiscard]] virtual Connection& connection() const = 0;
    [[nodiscard]] virtual Console& console() const = 0;
    [[nodiscard]] virtual Filesystem& filesystem() const = 0;
  };

} // namespace avansync