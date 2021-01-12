#pragma once

#include "Filesystem.hpp"
#include "fs.hpp"

namespace avansync
{

  class StandardFilesystem : public Filesystem
  {
  private:
    fs::path _base_dir;

  public:
    explicit StandardFilesystem(const std::string& base_dir);

    [[nodiscard]] std::unique_ptr<FileBuffer> read_file(const std::string& relative_path) const override;
    void overwrite_file(const std::string& path, FileBuffer& contents) const override;

    void remove(const std::string& relative_path) const override;

    void create_directories_for_file(const std::string& file_path) const override;

    std::vector<std::unique_ptr<DirectoryEntry>> directory_entries(const std::string& relative_path) const override;

  private:
    [[nodiscard]] fs::path full_path(const std::string& relative_path) const;
  };

} // namespace avansync
