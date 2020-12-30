#pragma once

#include "Console.hpp"
#include "connection/Connection.hpp"

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

    [[nodiscard]] virtual std::string base_dir_path() const = 0;
  };

} // namespace avansync