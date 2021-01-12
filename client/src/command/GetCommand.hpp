#pragma once

#include "Command.hpp"

namespace avansync::client::command
{

  class GetCommand : public Command
  {
  public:
    void execute(Context& context) const override;
  };

} // namespace avansync::client::command