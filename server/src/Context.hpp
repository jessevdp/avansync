#pragma once

#include <asio.hpp>
#include <iostream>
#include <string>

namespace avansync::server
{

  class Context
  {
  public:
    virtual ~Context() noexcept = default;

    [[nodiscard]] virtual asio::ip::tcp::iostream& client() const = 0;

    virtual void disconnect_current_client() = 0;

    virtual void log(const std::string&) const = 0;
    [[nodiscard]] virtual std::basic_ostream<char>& log() const = 0;

    [[nodiscard]] virtual std::string base_dir_path() const = 0;
  };

} // namespace avansync::server