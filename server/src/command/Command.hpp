#pragma once

#include "Context.hpp"

#include <string>
#include <vector>

namespace avansync::server::command
{

  class Command
  {
  protected:
    inline static const char* lf {"\n"};
    inline static const char* crlf {"\r\n"};

  public:
    virtual ~Command() noexcept = default;

    virtual void execute(Context& context, std::vector<std::string> args) const = 0;
  };

} // namespace avansync::server::command