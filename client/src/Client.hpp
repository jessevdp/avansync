#pragma once

#include "Context.hpp"
#include "connection/Connection.hpp"
#include "handler/RequestHandlerChain.hpp"

#include <iosfwd>
#include <memory>
#include <string>

namespace avansync::client
{

  class Client : public Context
  {
  private:
    inline static const char* prompt {"avansync> "};

    std::unique_ptr<Connection> _connection {nullptr};
    std::unique_ptr<handler::RequestHandlerChain> _handlers {nullptr};
    std::unique_ptr<Filesystem> _filesystem {nullptr};

  public:
    explicit Client(const std::string& base_dir_path);

    void connect_to(const std::string& server_address, const std::string& server_port);

    //#region Context

    [[nodiscard]] Connection& connection() const override;
    [[nodiscard]] Console& console() const override;
    [[nodiscard]] Filesystem& filesystem() const override;

    //#endregion

  private:
    void establish_connection(const std::string& server_address, const std::string& server_port);
    void on_connect() const;
    [[nodiscard]] std::string prompt_request() const;
    void handle_request(const std::string& request);
  };

} // namespace avansync::client
