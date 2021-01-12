#pragma once

#include "Command.hpp"

#include <string>

namespace avansync::server::command
{

  class DirectoryListingCommand : public Command
  {
  private:
    inline static const std::string TIMESTAMP_FORMAT = "%Y-%m-%d %H:%M:%S";

  public:
    void execute(Context& context) const override;
  };

} // namespace avansync::server::command
