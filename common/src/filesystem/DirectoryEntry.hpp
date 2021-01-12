#pragma once

#include <chrono>
#include <string>

namespace avansync
{

  class DirectoryEntry
  {
  public:
    virtual ~DirectoryEntry() = default;

    virtual bool is_regular_file() const = 0;
    virtual bool is_directory() const = 0;
    virtual bool is_symlink() const = 0;

    virtual std::string name() const = 0;

    /// File size in bytes, 0 for directories
    virtual unsigned long file_size() const = 0;

    virtual std::string formatted_modification_timestamp(const std::string& format) const = 0;
  };

} // namespace avansync