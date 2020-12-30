#include "InfoCommand.hpp"

namespace avansync::client::command
{

  void InfoCommand::execute(Context& context) const
  {
    context.connection().write_line("info");
    context.console().write_line(context.connection().read_line());
  }

} // namespace avansync::client::command