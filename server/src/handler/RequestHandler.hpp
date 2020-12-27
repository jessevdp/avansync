#pragma once

#include "Context.hpp"

#include <memory>

namespace avansync::server::handler
{

  class RequestHandler
  {
  public:
    virtual ~RequestHandler() noexcept = default;

    virtual bool handle(const std::string& request, Context&) const = 0;
    virtual void link_next(std::unique_ptr<RequestHandler> next) = 0;
  };

} // namespace avansync::server::handler