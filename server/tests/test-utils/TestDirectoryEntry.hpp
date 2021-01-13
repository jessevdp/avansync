#pragma once

#include "filesystem/DirectoryEntry.hpp"

class TestDirectoryEntry : public avansync::DirectoryEntry
{
public:
  bool is_regular_file() const override;
  bool is_directory() const override;
  bool is_symlink() const override;
  std::string name() const override;
  std::string relative_path() const override;
  unsigned long file_size() const override;
  std::string formatted_modification_timestamp() const override;
};
