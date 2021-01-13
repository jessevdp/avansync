#include "CreateDirectoryCommand.hpp"

namespace avansync::server::command
{

  void CreateDirectoryCommand::execute(Context& context) const
  {
    auto parent_path = context.connection().read_line();
    auto dir_name = context.connection().read_line();

    try
    {
      context.filesystem().create_directory(parent_path, dir_name);
    }
    catch (const FilesystemException& e)
    {
      context.connection().write_exception(e);
      return;
    }

    context.connection().write_line("OK");
  }

} // namespace avansync::server::command