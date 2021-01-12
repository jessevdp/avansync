#include "GetCommand.hpp"

#include "filesystem/fs.hpp"

#include <fstream>

namespace avansync::client::command
{

  void GetCommand::execute(Context& context) const
  {
    context.connection().write_line("get");

    context.console().write("file: ");
    auto file_name = context.console().read_line();
    context.connection().write_line(file_name);

    int file_size = std::stoi(context.connection().read_line());

    // Read file contents from stream into buffer
    std::vector<char> file_buffer;
    file_buffer.reserve(file_size);
    context.connection().read_bytes(file_size, file_buffer.data());

    // TODO: debug info?

    // TODO: generalize and move
    // Attempt to write the file to disk

    fs::path path {context.base_dir_path()};
    path.append(file_name);

    fs::create_directories(path.parent_path());

    std::ofstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);

    try
    {
      file.open(path, std::ios::binary | std::ios::trunc);
      file.write(file_buffer.data(), file_size);
      file.close();
    }
    catch (std::ios::failure& failure)
    {
      // TODO: error details?
      throw std::runtime_error {"problem writing to file: '" + path.string() + "'"};
    }

    context.console().write_line("OK");
  }

} // namespace avansync::client::command