#include "QuitCommand.hpp"

namespace avansync::client::command
{

  void QuitCommand::execute(Context& context) const
  {
    context.connection().write_line("quit");
    context.connection().close();
  }

} // namespace avansync::client::command