#include "PutCommand.hpp"

namespace avansync::client::command
{

  void PutCommand::execute(Context& context) const
  {
    context.console().write("file: ");
    auto filename = context.console().read_line();

    // TODO: debug info?

    // Read file from disk
    auto file = context.filesystem().read_file(filename);

    // Communicate details of request to server
    context.connection().write_line("put");
    context.connection().write_line(filename);
    context.connection().write_line(std::to_string(file->size()));
    // Write file contents to server
    context.connection().write_bytes(file->size(), file->data());

    // Communicate server response to user
    context.console().write_line(context.connection().read_line());
  }

} // namespace avansync::client::command