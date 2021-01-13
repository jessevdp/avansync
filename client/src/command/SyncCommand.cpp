#include "SyncCommand.hpp"

#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

namespace avansync::client::command
{

  void SyncCommand::execute(Context& context) const
  {
    context.console().write("directory: ");
    auto path = context.console().read_line();

    sync_directory_recursively(context, path);

    context.console().write_line("OK");
  }

  void SyncCommand::sync_directory_recursively(Context& context, const std::string& path) const
  {
    auto local_entries = context.filesystem().directory_entries(path);

    // Handle directories first. Making sure to remove them from the "to be handled" list of entries
    auto it = local_entries.begin();
    while (it != local_entries.end())
    {
      auto& entry = *it;
      if (entry->is_directory())
      {
        sync_directory_recursively(context, entry->relative_path());
        it = local_entries.erase(it);
        continue;
      }
      ++it;
    }

    // Compare files in remote dir to local dir

    int remote_entry_count {0};

    try
    {
      // TODO: this is duplicate from DirectoryListingCommand
      context.connection().write_line("dir");
      context.connection().write_line(path);
      remote_entry_count = std::stoi(context.connection().read_line());
    }
    catch (std::exception& e)
    {
      // the remote dir does not exist, create it
      construct_remote_directory_recursively(context, path);
    }

    for (int i = 0; i < remote_entry_count; ++i)
    {
      auto remote_entry_line = split(context.connection().read_line(), '|');
      auto type = remote_entry_line[0];
      auto name = remote_entry_line[1];
      auto formatted_timestamp = remote_entry_line[2];

      // skip dirs
      if (type == "D") continue;

      auto local_entry_it =
        std::find_if(local_entries.begin(), local_entries.end(), [&name](const auto& local) { local->name() == name; });
      auto local_entry = local_entry_it->get();

      if (local_entry)
      {
        if (local_entry->formatted_modification_timestamp() != formatted_timestamp)
        {
          // TODO: this is duplicate from PutCommand...
          // Read file from disk
          auto file = context.filesystem().read_file(local_entry->relative_path());

          // Communicate details of request to server
          context.connection().write_line("put");
          context.connection().write_line(local_entry->relative_path());
          context.connection().write_line(std::to_string(file->size()));
          // Write file contents to server
          context.connection().write_bytes(file->size(), file->data());

          // read response from server (prevent blocking)
          auto response = context.connection().read_line();
        }
        local_entries.erase(local_entry_it);
      }
      else
      {
        // Entry does not exist locally -> delete on remote
        // TODO: this is duplicate from DeleteCommand
        context.connection().write_line("del");
        context.connection().write_line(path);

        // read response from server (prevent blocking)
        auto response = context.connection().read_line();
      }
    }

    // Upload files missing from remote dir
    // (the ones we haven't encountered when comparing to the remote dir don't exist there and should be uploaded)
    for (const auto& entry : local_entries)
    {
      // TODO: this is duplicate from PutCommand...
      // Read file from disk
      auto file = context.filesystem().read_file(entry->relative_path());

      // Communicate details of request to server
      context.connection().write_line("put");
      context.connection().write_line(entry->relative_path());
      context.connection().write_line(std::to_string(file->size()));
      // Write file contents to server
      context.connection().write_bytes(file->size(), file->data());

      // read response from server (prevent blocking)
      auto response = context.connection().read_line();
    }
  }

  void SyncCommand::construct_remote_directory_recursively(Context& context, const std::string& path) const
  {
    std::string parent_path = context.filesystem().parent_path(path);
    std::string dir_name = context.filesystem().filename(path);

    try
    {
      context.connection().write_line("mkdir");
      context.connection().write_line(parent_path);
      context.connection().write_line(dir_name);
      auto response = context.connection().read_line(); // throws when problem on remote
    }
    catch (const std::exception& e)
    {
      // parent dir also does not exist, first create it then re-attempt to create this dir
      construct_remote_directory_recursively(context, parent_path);
      // TODO: this could create an infinite loop if something unexpected happens
      construct_remote_directory_recursively(context, path);
    }
  }

} // namespace avansync::client::command