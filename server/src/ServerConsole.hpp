#pragma once

#include "Console.hpp"

namespace avansync::server
{

  class ServerConsole : public Console
  {
  private:
    inline static const char* lf {"\n"};

  public:
    void write(const std::string& data) const override;
    void write_line(const std::string& data) const override;
    std::string read_line() const override;

    // #region singleton
  public:
    static ServerConsole& instance();

  private:
    // class is only accessible through the singleton interface and can not be constructed from the outside
    ServerConsole() {};

  public:
    // delete all ways to copy the class, making sure the singleton instance is the only instance
    ServerConsole(const ServerConsole&) = delete;
    void operator=(const ServerConsole&) = delete;

    //#endregion
  };

} // namespace avansync::client
