#include "InfoCommand.hpp"

namespace avansync::server::command
{

  void InfoCommand::execute(avansync::server::Context& context) const
  {
    context.client() << "AvanSync server 1.0" << crlf;
  }

} // namespace avansync::server::command
