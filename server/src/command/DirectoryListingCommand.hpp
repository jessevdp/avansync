#pragma once

#include "Command.hpp"

#include <string>

namespace avansync::server::command
{

  class DirectoryListingCommand : public Command
  {
  public:
    void execute(Context& context) const override;
  };

} // namespace avansync::server::command
