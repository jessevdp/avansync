#include "PutCommand.hpp"

#include "filesystem/fs.hpp"

#include <fstream>
#include <vector>

namespace avansync::client::command
{

  void PutCommand::execute(Context& context) const
  {
    context.console().write("file: ");
    auto filename = context.console().read_line();

    fs::path path {context.base_dir_path()};
    path.append(filename); // TODO: this exposes the entire client file system...

    if (!fs::exists(path) || !fs::is_regular_file(path)) throw std::runtime_error {"no such file"};

    int file_size = fs::file_size(path);

    // Copy file contents to buffer
    std::vector<char> file_buffer;
    file_buffer.reserve(file_size);
    std::ifstream file {path, std::ifstream::binary};
    if (!file)
    {
      // TODO: error details?
      throw std::runtime_error {"problem reading file '" + path.string() + "'"};
    }
    file.read(file_buffer.data(), file_size);
    file.close();

    // Communicate details of request to server
    context.connection().write_line("put");
    context.connection().write_line(filename);
    context.connection().write_line(std::to_string(file_size));
    // Write file contents to server
    context.connection().write_bytes(file_size, file_buffer.data());

    context.console().write_line(context.connection().read_line());
  }

} // namespace avansync::client::command