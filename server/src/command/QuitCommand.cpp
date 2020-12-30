#include "QuitCommand.hpp"

namespace avansync::server::command
{

  void QuitCommand::execute(Context& context) const
  {
    context.connection().write_line("Bye.");
    context.console().write_line("will disconnect from client " + context.connection().local_endpoint_name());
    context.connection().close();
  }

} // namespace avansync::server::command