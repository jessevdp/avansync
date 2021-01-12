#include "StandardDirectoryEntry.hpp"

#include <iomanip>
#include <sstream>

namespace avansync
{

  StandardDirectoryEntry::StandardDirectoryEntry(std::unique_ptr<fs::directory_entry> entry) : _entry {std::move(entry)}
  {}

  bool StandardDirectoryEntry::is_regular_file() const { return fs::is_regular_file(*_entry); }

  bool StandardDirectoryEntry::is_directory() const { return fs::is_directory(*_entry); }

  bool StandardDirectoryEntry::is_symlink() const { return fs::is_symlink(*_entry); }

  std::string StandardDirectoryEntry::name() const { return _entry->path().filename().string(); }

  unsigned long StandardDirectoryEntry::file_size() const
  {
    unsigned long size = 0;
    if (is_regular_file() && !is_symlink()) { size = fs::file_size(*_entry); }
    return size;
  }

  std::string StandardDirectoryEntry::formatted_modification_timestamp(const std::string& format) const
  {
    auto timestamp = fs::last_write_time(*_entry);
    auto timestamp_t = decltype(timestamp)::clock::to_time_t(timestamp);

    std::stringstream formatted_timestamp;
    formatted_timestamp << std::put_time(std::localtime(&timestamp_t), format.c_str());

    return formatted_timestamp.str();
  }

} // namespace avansync