#include "DeleteCommand.hpp"

namespace avansync::server::command
{

  void DeleteCommand::execute(Context& context) const
  {
    auto path = context.connection().read_line();
    try
    {
      context.filesystem().remove(path);
    }
    catch (const FilesystemException& e)
    {
      context.connection().write_exception(e);
      return;
    }

    context.connection().write_line("OK");
  }

} // namespace avansync::server::command