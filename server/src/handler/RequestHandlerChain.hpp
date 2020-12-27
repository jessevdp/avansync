#pragma once

#include "RequestHandler.hpp"

#include <memory>

namespace avansync::server::handler
{

  class RequestHandlerChain
  {
  private:
    std::unique_ptr<RequestHandler> _first {nullptr};
    RequestHandler* _last {nullptr};

  public:
    void add(std::unique_ptr<RequestHandler> handler);
    bool handle(const std::string&, Context&) const;
  };

} // namespace avansync::server::handler