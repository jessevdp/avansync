#include "CreateDirectoryCommand.hpp"

namespace avansync::client::command
{

  void CreateDirectoryCommand::execute(Context& context) const
  {
    context.console().write("parent directory: ");
    auto parent_path = context.console().read_line();

    context.console().write("new directory name: ");
    auto dir_name = context.console().read_line();

    context.connection().write_line("mkdir");
    context.connection().write_line(parent_path);
    context.connection().write_line(dir_name);

    context.console().write_line(context.connection().read_line());
  }

} // namespace avansync::client::command