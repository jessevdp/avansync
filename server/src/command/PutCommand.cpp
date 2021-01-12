#include "PutCommand.hpp"

#include "filesystem/VectorFileBuffer.hpp"

namespace avansync::server::command
{

  void PutCommand::execute(Context& context) const
  {
    auto filename = context.connection().read_line();
    int file_size = std::stoi(context.connection().read_line());

    // TODO: debug info?

    VectorFileBuffer buffer {file_size};

    // Read file contents from stream into buffer
    context.connection().read_bytes(buffer.size(), buffer.data());

    try
    {
      context.filesystem().overwrite_file(filename, buffer);
    }
    catch (FilesystemException& e)
    {
      context.connection().write_exception(e);
      return;
    }

    context.connection().write_line("OK");
  }

} // namespace avansync::server::command