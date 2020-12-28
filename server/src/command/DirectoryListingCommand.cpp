#include "DirectoryListingCommand.hpp"

#include <filesystem>

namespace fs = std::filesystem;

namespace avansync::server::command
{
  //#region helpers

  char file_type(const fs::directory_entry& entry)
  {
    char type = '*';

    if (entry.is_symlink())
    {
      // treat as 'other'
    }
    else if (entry.is_directory())
    {
      type = 'D';
    }
    else if (entry.is_regular_file())
    {
      type = 'F';
    }

    return type;
  }

  unsigned long file_size(const fs::directory_entry& entry)
  {
    unsigned long size = 0;
    if (entry.is_regular_file() && !entry.is_symlink()) { size = entry.file_size(); }
    return size;
  }

  std::string modification_timestamp(const fs::directory_entry& entry)
  {
    auto timestamp = entry.last_write_time();
    auto timestamp_t = decltype(timestamp)::clock::to_time_t(timestamp);

    std::stringstream formatted_timestamp;
    formatted_timestamp << std::put_time(std::localtime(&timestamp_t), DirectoryListingCommand::TIMESTAMP_FORMAT);

    return formatted_timestamp.str();
  }

  //#endregion

  void DirectoryListingCommand::execute(Context& context) const
  {
    std::string path = context.base_dir_path();

    int item_count = std::distance(fs::directory_iterator(path), fs::directory_iterator {});
    context.connection().write_line(std::to_string(item_count));

    for (const auto& entry : fs::directory_iterator(path))
    {
      char type = file_type(entry);
      unsigned long size = file_size(entry);
      auto name = entry.path().filename().string();
      auto timestamp = modification_timestamp(entry);

      std::stringstream file_info;
      file_info << type << "|" << name << "|" << timestamp << "|" << size;

      context.connection().write_line(file_info.str());
    }
  }

} // namespace avansync::server::command