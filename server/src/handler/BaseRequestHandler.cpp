#include "BaseRequestHandler.hpp"

namespace avansync::server::handler
{

  bool BaseRequestHandler::handle(const Request& request, Context& context) const
  {
    if (do_handle(request, context)) return true;
    if (_next) return _next->handle(request, context);
    return false;
  }

  void BaseRequestHandler::link_next(std::unique_ptr<RequestHandler> next)
  {
    _next = std::move(next);
  }

} // namespace avansync::server::handler