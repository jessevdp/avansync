#pragma once

#include "Command.hpp"

namespace avansync::client::command
{

  class SyncCommand : public Command
  {
  public:
    void execute(Context& context) const override;

  private:
    void sync_directory_recursively(Context& context, const std::string& path) const;
    void construct_remote_directory_recursively(Context& context, const std::string& path) const;
  };

} // namespace avansync::client::command