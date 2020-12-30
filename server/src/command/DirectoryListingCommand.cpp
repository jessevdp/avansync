#include "DirectoryListingCommand.hpp"

#include "filesystem/fs.hpp"

#include <iomanip>

namespace avansync::server::command
{
  //#region helpers

  char file_type(const fs::directory_entry& entry)
  {
    char type = '*';

    if (fs::is_symlink(entry))
    {
      // treat as 'other'
    }
    else if (fs::is_directory(entry))
    {
      type = 'D';
    }
    else if (fs::is_regular_file(entry))
    {
      type = 'F';
    }

    return type;
  }

  unsigned long file_size(const fs::directory_entry& entry)
  {
    unsigned long size = 0;
    if (fs::is_regular_file(entry) && !fs::is_symlink(entry)) { size = fs::file_size(entry); }
    return size;
  }

  std::string modification_timestamp(const fs::directory_entry& entry)
  {
    auto timestamp = fs::last_write_time(entry);
    auto timestamp_t = decltype(timestamp)::clock::to_time_t(timestamp);

    std::stringstream formatted_timestamp;
    formatted_timestamp << std::put_time(std::localtime(&timestamp_t), DirectoryListingCommand::TIMESTAMP_FORMAT);

    return formatted_timestamp.str();
  }

  //#endregion

  void DirectoryListingCommand::execute(Context& context) const
  {
    fs::path path {context.base_dir_path()};
    path.append(context.connection().read_line()); // TODO: this exposes the entire server file system...

    if (!fs::exists(path) || !fs::is_directory(path))
    {
      context.connection().write_exception("no such directory");
      return;
    }

    int item_count = std::distance(fs::directory_iterator(path), fs::directory_iterator {});
    context.connection().write_line(std::to_string(item_count));

    for (const auto& entry : fs::directory_iterator(path))
    {
      std::stringstream file_info;
      file_info << file_type(entry);
      file_info << "|" << entry.path().filename().string();
      file_info << "|" << modification_timestamp(entry);
      file_info << "|" << file_size(entry);

      context.connection().write_line(file_info.str());
    }
  }

} // namespace avansync::server::command