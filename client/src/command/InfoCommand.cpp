#include "InfoCommand.hpp"

namespace avansync::client::command
{

  void InfoCommand::execute(Context& context) const
  {
    context.connection().write_line("info");
    context.log() << context.connection().read_line() << lf;
  }

} // namespace avansync::client::command