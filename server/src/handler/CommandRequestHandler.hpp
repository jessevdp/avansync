#pragma once

#include "BaseRequestHandler.hpp"
#include "command/Command.hpp"

#include <memory>

namespace avansync::server::handler
{

  class CommandRequestHandler : public BaseRequestHandler
  {
  private:
    std::string _name;
    std::unique_ptr<command::Command> _command;

  public:
    CommandRequestHandler(std::string name, std::unique_ptr<command::Command> command);

  protected:
    bool do_handle(const Request& request, Context& context) const override;
  };

} // namespace avansync::server::handler