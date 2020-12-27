#include "RequestHandlerChain.hpp"

namespace avansync::server::handler
{

  void RequestHandlerChain::add(std::unique_ptr<RequestHandler> handler)
  {
    RequestHandler* handler_raw {handler.get()};

    if (_first) { _last->link_next(std::move(handler)); }
    else
    {
      _first = std::move(handler);
    }

    _last = handler_raw;
  }

  bool RequestHandlerChain::handle(const std::string& request, Context& context) const
  {
    if (_first) return _first->handle(request, context);
    return false;
  }

} // namespace avansync::server::handler
