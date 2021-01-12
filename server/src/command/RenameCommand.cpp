#include "RenameCommand.hpp"

namespace avansync::server::command
{

  void RenameCommand::execute(Context& context) const
  {
    auto path = context.connection().read_line();
    auto new_name = context.connection().read_line();

    try
    {
      context.filesystem().rename(path, new_name);
    }
    catch (const FilesystemException& e)
    {
      context.connection().write_exception(e);
      return;
    }

    context.connection().write_line("OK");
  }

} // namespace avansync::server::command