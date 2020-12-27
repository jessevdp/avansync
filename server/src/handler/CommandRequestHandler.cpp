#include "CommandRequestHandler.hpp"

#include <utility>

namespace avansync::server::handler
{

  CommandRequestHandler::CommandRequestHandler(std::string name, std::unique_ptr<command::Command> command) :
      _name {std::move(name)}, _command {std::move(command)}
  {}

  bool CommandRequestHandler::do_handle(const Request& request, Context& context) const
  {
    if (_name == request.command())
    {
      _command->execute(context, request.args());
      return true;
    }
    return false;
  }

} // namespace avansync::server::handler