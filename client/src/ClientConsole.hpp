#pragma once

#include "Console.hpp"

namespace avansync::client
{

  class ClientConsole : public Console
  {
  private:
    inline static const char* lf {"\n"};

  public:
    void write(const std::string& data) const override;
    void write_line(const std::string& data) const override;
    std::string read_line() const override;

    // #region singleton
  public:
    static ClientConsole& instance();

  private:
    // class is only accessible through the singleton interface and can not be constructed from the outside
    ClientConsole() {};

  public:
    // delete all ways to copy the class, making sure the singleton instance is the only instance
    ClientConsole(const ClientConsole&) = delete;
    void operator=(const ClientConsole&) = delete;

    //#endregion
  };

} // namespace avansync::client
