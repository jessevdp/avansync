#include "StandardFilesystem.hpp"

#include "VectorFileBuffer.hpp"

#include <fstream>

namespace avansync::filesystem
{

  StandardFilesystem::StandardFilesystem(const std::string& base_dir) : _base_dir {base_dir}
  {
    if (!fs::exists(_base_dir) || !fs::is_directory(_base_dir))
    {
      std::string message = "invalid base directory [" + base_dir + "]";
      throw FilesystemException {message};
    }
  }

  std::unique_ptr<FileBuffer> StandardFilesystem::read_file(const std::string& relative_path) const
  {
    auto path = full_path(relative_path);
    if (!fs::exists(path) || !fs::is_regular_file(path)) throw FilesystemException {"no such file"};

    int file_size = fs::file_size(path);
    auto buffer = std::make_unique<VectorFileBuffer>(file_size);

    std::ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);

    try
    {
      file.open(path);
      file.read(buffer->data(), buffer->size());
      file.close();
    }
    catch (std::ios::failure& failure)
    {
      if (failure.code() == std::errc::permission_denied) { throw FilesystemException {"no permission"}; }
      else
      {
        auto m = "problem reading file (file: '" + relative_path + "', error: '" + failure.code().message() + "')";
        throw FilesystemException {m};
      }
    }

    return buffer;
  }

  void StandardFilesystem::overwrite_file(const std::string& relative_path, FileBuffer& contents) const
  {
    auto path = full_path(relative_path);

    if (!fs::exists(path.parent_path()) && !fs::is_directory(path.parent_path()))
    { throw FilesystemException {"invalid path"}; }

    std::ofstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);

    try
    {
      file.open(path, std::ios::binary | std::ios::trunc);
      file.write(contents.data(), contents.size());
      file.close();
    }
    catch (std::ios::failure& failure)
    {
      if (failure.code() == std::errc::permission_denied) { throw FilesystemException {"no permission"}; }
      else if (failure.code() == std::errc::file_too_large)
      {
        throw FilesystemException {"not enough disk space"};
      }
      else
      {
        auto m = "problem overwriting file (file: '" + relative_path + "', error: '" + failure.code().message() + "')";
        throw FilesystemException {m};
      }
    }
  }

  fs::path StandardFilesystem::full_path(const std::string& relative_path) const
  {
    fs::path full {_base_dir};
    full.append(relative_path);
    return full;
  }

} // namespace avansync::filesystem
