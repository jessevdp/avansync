#pragma once

#include "Context.hpp"

#include <string>
#include <vector>

namespace avansync
{

  class Command
  {
  public:
    virtual ~Command() noexcept = default;

    virtual void execute(Context& context) const = 0;
  };

} // namespace avansync