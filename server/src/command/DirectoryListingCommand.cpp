#include "DirectoryListingCommand.hpp"

namespace avansync::server::command
{
  //#region helpers

  char file_type(const DirectoryEntry& entry)
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

  //#endregion

  void DirectoryListingCommand::execute(Context& context) const
  {
    auto dirname = context.connection().read_line();

    auto entries = context.filesystem().directory_entries(dirname);

    context.connection().write_line(std::to_string(entries.size()));

    for (const auto& entry : entries)
    {
      std::stringstream file_info;
      file_info << file_type(*entry);
      file_info << "|" << entry->name();
      file_info << "|" << entry->formatted_modification_timestamp(TIMESTAMP_FORMAT);
      file_info << "|" << entry->file_size();

      context.connection().write_line(file_info.str());
    }
  }

} // namespace avansync::server::command