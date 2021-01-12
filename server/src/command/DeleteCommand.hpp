#pragma once

#include "Command.hpp"

namespace avansync::server::command
{

  class DeleteCommand : public Command
  {
  public:
    void execute(Context& context) const override;
  };

} // namespace avansync::server::command