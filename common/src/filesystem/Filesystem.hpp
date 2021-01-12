#pragma once

#include "DirectoryEntry.hpp"
#include "FileBuffer.hpp"
#include "FilesystemException.hpp"

#include <memory>
#include <vector>

namespace avansync
{

  class Filesystem
  {
  public:
    virtual ~Filesystem() = default;

    virtual std::unique_ptr<FileBuffer> read_file(const std::string& path) const = 0;
    virtual void overwrite_file(const std::string& path, FileBuffer& contents) const = 0;

    virtual std::vector<std::unique_ptr<DirectoryEntry>> directory_entries(const std::string& path) const = 0;

    virtual void create_directories_for_file(const std::string& file_path) const = 0;
  };

} // namespace avansync
