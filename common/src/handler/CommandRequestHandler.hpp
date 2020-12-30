#pragma once

#include "BaseRequestHandler.hpp"
#include "Command.hpp"

#include <memory>

namespace avansync::handler
{

  class CommandRequestHandler : public BaseRequestHandler
  {
  private:
    std::string _name;
    std::unique_ptr<Command> _command;

  public:
    CommandRequestHandler(std::string name, std::unique_ptr<Command> command);

  protected:
    bool do_handle(const std::string& request, Context& context) const override;
  };

} // namespace avansync::handler