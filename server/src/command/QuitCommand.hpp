#pragma once

#include "Command.hpp"

namespace avansync::server::command
{

  class QuitCommand : public Command
  {
  public:
    void execute(Context& context, std::vector<std::string> args) const override;
  };

} // namespace avansync::server::command
