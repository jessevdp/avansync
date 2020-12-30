#include "DirectoryListingCommand.hpp"

#ifdef CXX_FILESYSTEM_IS_EXPERIMENTAL
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

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
    fs::path path {context.base_dir_path()};
    path.append(context.connection().read_line()); // TODO: this exposes the entire server file system...

    if (!fs::exists(path) || !fs::is_directory(path))
    {
      // TODO: proper error handling structure.
      // The current form of error handling here just abuses the 'protocol' between client and server to
      // show an error message to the client. This isn't robust. Nor is it reusable for other commands.

      context.connection().write_line("1");
      context.connection().write_line("Error: no such directory");
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