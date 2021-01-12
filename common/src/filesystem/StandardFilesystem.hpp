#pragma once

#include "Filesystem.hpp"
#include "fs.hpp"

namespace avansync::filesystem
{

  class StandardFilesystem : public Filesystem
  {
  private:
    fs::path _base_dir;

  public:
    explicit StandardFilesystem(const std::string& base_dir);

    [[nodiscard]] std::unique_ptr<FileBuffer> read_file(const std::string& relative_path) const override;
    void overwrite_file(const std::string& relative_path, FileBuffer& contents) const override;

  private:
    [[nodiscard]] fs::path full_path(const std::string& relative_path) const;
  };

} // namespace avansync::filesystem
