#include "GetCommand.hpp"

#include "filesystem/VectorFileBuffer.hpp"

namespace avansync::client::command
{

  void GetCommand::execute(Context& context) const
  {
    context.connection().write_line("get");

    context.console().write("file: ");
    auto filename = context.console().read_line();
    context.connection().write_line(filename);

    int file_size = std::stoi(context.connection().read_line());

    // TODO: debug info?

    // Read file contents from server into buffer
    VectorFileBuffer buffer {file_size};
    context.connection().read_bytes(buffer.size(), buffer.data());

    // Write file contents from buffer to disk
    context.filesystem().create_directories_for_file(filename);
    context.filesystem().overwrite_file(filename, buffer);

    // Communicate completion to user
    context.console().write_line("OK");
  }

} // namespace avansync::client::command