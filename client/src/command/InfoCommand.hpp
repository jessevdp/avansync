#pragma once

#include "Command.hpp"

namespace avansync::client::command {

  class InfoCommand : public Command
  {
  public:
    void execute(Context& context) const override;
  };

}
