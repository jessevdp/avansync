#include "RenameCommand.hpp"

namespace avansync::client::command
{

  void RenameCommand::execute(Context& context) const
  {
    context.console().write("path: ");
    auto path = context.console().read_line();

    context.console().write("new name: ");
    auto new_name = context.console().read_line();

    context.connection().write_line("ren");
    context.connection().write_line(path);
    context.connection().write_line(new_name);

    context.console().write_line(context.connection().read_line());
  }

} // namespace avansync::client::command