#pragma once

#include "RequestHandler.hpp"

namespace avansync::server::handler
{

  class BaseRequestHandler : public RequestHandler
  {
  private:
    std::unique_ptr<RequestHandler> _next {nullptr};

  public:
    ~BaseRequestHandler() noexcept override = default;
    bool handle(const std::string&, Context&) const override;
    void link_next(std::unique_ptr<RequestHandler> next) override;

  protected:
    virtual bool do_handle(const std::string&, Context&) const = 0;
  };

} // namespace avansync::server::handler