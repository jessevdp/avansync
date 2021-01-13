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

    virtual void remove(const std::string& path) const = 0;

    virtual void rename(const std::string& path, const std::string& new_name) const = 0;

    virtual std::vector<std::unique_ptr<DirectoryEntry>> directory_entries(const std::string& path) const = 0;

    virtual void create_directory(const std::string& parent_dir, const std::string& dir_name) const = 0;
    virtual void create_directories_for_file(const std::string& file_path) const = 0;

    virtual std::string parent_path(const std::string& path) const = 0;
    virtual std::string filename(const std::string& path) const = 0;
    virtual std::string append_path(const std::string& parent_path, const std::string& relative_path) const = 0;
  };

} // namespace avansync
