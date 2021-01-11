#include "PutCommand.hpp"

#include "filesystem/fs.hpp"

#include <fstream>
#include <vector>

namespace avansync::server::command
{

  void PutCommand::execute(Context& context) const
  {
    fs::path path {context.base_dir_path()};
    path.append(context.connection().read_line()); // TODO: this exposes the entire server file system...

    int file_size = std::stoi(context.connection().read_line());

    // Read file contents from stream into buffer
    std::vector<char> file_buffer;
    file_buffer.reserve(file_size);
    context.connection().read_bytes(file_size, file_buffer.data());

    // Attempt to write file to disk

    bool parent_dir_exists = fs::exists(path.parent_path()) && fs::is_directory(path.parent_path());
    bool path_is_existing_dir = fs::exists(path) && fs::is_directory(path); // TODO: is this required?
    if (!parent_dir_exists || path_is_existing_dir)
    {
      context.connection().write_exception("invalid path");
      return;
    }

    std::ofstream file {path, std::ofstream::binary | std::ofstream::trunc};
    if (!file)
    {
      // TODO: error details?
      //  - handle "no permission"
      //  - handle "not enough disk space"
      context.connection().write_exception("problem writing to file");
      return;
    }
    file.write(file_buffer.data(), file_size);
    file.close();

    context.connection().write_line("OK");
  }

} // namespace avansync::server::command