#include "QuitCommand.hpp"

namespace avansync::client::command
{

  void QuitCommand::execute(Context& context) const {
    context.connection().write_line("quit");
    context.log() << context.connection().read_line() << lf;
    context.connection().close();
  }

}