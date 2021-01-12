#include "GetCommand.hpp"

namespace avansync::server::command
{

  void GetCommand::execute(Context& context) const
  {
    auto filename = context.connection().read_line();

    // TODO: debug info?

    try
    {
      auto file = context.filesystem().read_file(filename);
      context.connection().write_line(std::to_string(file->size()));
      context.connection().write_bytes(file->size(), file->data());
    }
    catch (FilesystemException& e)
    {
      context.connection().write_exception(e);
    }
  }

} // namespace avansync::server::command