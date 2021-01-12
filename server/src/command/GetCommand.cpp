#include "GetCommand.hpp"

#include "filesystem/fs.hpp"

#include <fstream>

namespace avansync::server::command
{

  void GetCommand::execute(Context& context) const
  {
    fs::path path {context.base_dir_path()};
    path.append(context.connection().read_line()); // TODO: this exposes the entire server file system...

    if (!fs::exists(path) || !fs::is_regular_file(path))
    {
      context.connection().write_exception("no such file");
      return;
    }

    int file_size = fs::file_size(path);

    // Copy file contents to buffer
    std::vector<char> file_buffer;
    file_buffer.reserve(file_size);

    std::ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);

    try
    {
      file.open(path);
      file.read(file_buffer.data(), file_size);
      file.close();
    }
    catch (std::ios::failure& failure)
    {
      // TODO: error detais?
      context.connection().write_exception("problem reading file");
      return;
    }

    context.connection().write_line(std::to_string(file_size));
    context.connection().write_bytes(file_size, file_buffer.data());
  }

} // namespace avansync::server::command