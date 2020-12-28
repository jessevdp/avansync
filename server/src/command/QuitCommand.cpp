#include "QuitCommand.hpp"

namespace avansync::server::command
{

  void QuitCommand::execute(Context& context) const
  {
    context.connection().write_line("Bye.");
    context.log() << "will disconnect from client " << context.connection().local_endpoint_name() << lf;
    context.disconnect_current_client();
  }

} // namespace avansync::server::command