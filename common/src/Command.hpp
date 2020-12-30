#pragma once

#include "Context.hpp"

#include <string>
#include <vector>

namespace avansync
{

  class Command
  {
  protected:
    inline static const char* lf {"\n"};

  public:
    virtual ~Command() noexcept = default;

    virtual void execute(Context& context) const = 0;
  };

} // namespace avansync