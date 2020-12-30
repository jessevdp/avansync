#pragma once

#include "Command.hpp"

namespace avansync::server::command
{

  class DirectoryListingCommand : public Command
  {
  public:
    inline static const char* TIMESTAMP_FORMAT = "%Y-%m-%d %H:%M:%S";

  public:
    void execute(Context& context) const override;
  };

} // namespace avansync::server::command
