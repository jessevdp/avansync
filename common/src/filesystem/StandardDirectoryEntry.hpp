#pragma once

#include "DirectoryEntry.hpp"
#include "fs.hpp"

namespace avansync
{

  class StandardDirectoryEntry : public DirectoryEntry
  {
  private:
    std::unique_ptr<fs::directory_entry> _entry {nullptr};

  public:
    StandardDirectoryEntry(std::unique_ptr<fs::directory_entry> entry);

    bool is_regular_file() const override;
    bool is_directory() const override;
    bool is_symlink() const override;
    std::string name() const override;
    unsigned long file_size() const override;
    std::string formatted_modification_timestamp(const std::string& format) const override;
  };

} // namespace avansync
