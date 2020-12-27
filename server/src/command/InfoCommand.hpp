#pragma once

#include "Command.hpp"

namespace avansync::server::command
{

  class InfoCommand : public Command
  {
  public:
    void execute(Context& context) const override;
  };

} // namespace avansync::server::command
