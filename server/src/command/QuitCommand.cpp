#include "QuitCommand.hpp"

namespace avansync::server::command {

  void QuitCommand::execute(Context& context, std::vector<std::string> args) const
  {
    context.client() << "Bye." << crlf;
    context.log() << "will disconnect from client " << context.client().socket().local_endpoint() << lf;
    context.disconnect_current_client();
  }

}