#pragma once

#include "FileBuffer.hpp"
#include "FilesystemException.hpp"

#include <memory>

namespace avansync
{

  class Filesystem
  {
  public:
    virtual ~Filesystem() = default;

    virtual std::unique_ptr<FileBuffer> read_file(const std::string& path) const = 0;
    virtual void overwrite_file(const std::string& path, FileBuffer& contents) const = 0;

    virtual void create_directories_for_file(const std::string& file_path) const = 0;
  };

} // namespace avansync
