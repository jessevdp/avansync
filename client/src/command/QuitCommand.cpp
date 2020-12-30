#include "QuitCommand.hpp"

namespace avansync::client::command
{

  void QuitCommand::execute(Context& context) const
  {
    context.connection().write_line("quit");
    context.console().write_line(context.connection().read_line());
    context.connection().close();
  }

} // namespace avansync::client::command