#include "DirectoryListingCommand.hpp"

namespace avansync::client::command
{

  void DirectoryListingCommand::execute(Context& context) const
  {
    context.connection().write_line("dir");

    context.console().write("sub-directory: ");
    auto dir = context.console().read_line();

    context.connection().write_line(dir);

    int entry_count = std::stoi(context.connection().read_line());
    for (int i = 0; i < entry_count; ++i)
    {
      context.console().write_line(context.connection().read_line());
    }
  }

} // namespace avansync::client::command