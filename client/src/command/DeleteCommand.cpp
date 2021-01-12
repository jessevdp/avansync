#include "DeleteCommand.hpp"

namespace avansync::client::command
{

  void DeleteCommand::execute(Context& context) const
  {
    context.console().write("path: ");
    auto path = context.console().read_line();

    context.connection().write_line("del");
    context.connection().write_line(path);

    context.console().write_line(context.connection().read_line());
  }

} // namespace avansync::client::command