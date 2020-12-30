#include "CommandRequestHandler.hpp"

#include <utility>

namespace avansync::handler
{

  CommandRequestHandler::CommandRequestHandler(std::string name, std::unique_ptr<Command> command) :
      _name {std::move(name)}, _command {std::move(command)}
  {}

  bool CommandRequestHandler::do_handle(const std::string& request, Context& context) const
  {
    if (_name == request)
    {
      _command->execute(context);
      return true;
    }
    return false;
  }

} // namespace avansync::handler