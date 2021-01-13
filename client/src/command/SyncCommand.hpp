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

    // TODO: not most elegant solution
    static void put(Context& context, const std::string& relative_path);
    static void remove(Context& context, const std::string& relative_path);
    static std::vector<std::string> fetch_directory_listing(Context& context, const std::string& relative_path);
    static void create_directory(Context& context, const std::string& parent_path, const std::string& dir_name);
  };

} // namespace avansync::client::command