#include "InfoCommand.hpp"

namespace avansync::server::command
{

  void InfoCommand::execute(Context& context) const { context.connection().write_line("AvanSync server 1.0"); }

} // namespace avansync::server::command
