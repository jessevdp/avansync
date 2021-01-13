#pragma once

#include "DirectoryEntry.hpp"
#include "fs.hpp"

namespace avansync
{

  class StandardDirectoryEntry : public DirectoryEntry
  {
  private:
    std::unique_ptr<fs::directory_entry> _entry {nullptr};
    fs::path _base_dir;

  public:
    StandardDirectoryEntry(std::unique_ptr<fs::directory_entry> entry, fs::path base_dir);

    bool is_regular_file() const override;
    bool is_directory() const override;
    bool is_symlink() const override;

    std::string name() const override;
    std::string relative_path() const override;
    unsigned long file_size() const override;
    std::string formatted_modification_timestamp() const override;
  };

} // namespace avansync
