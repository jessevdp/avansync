#pragma once

#include <string>
#include <vector>

namespace avansync::server
{

  class Request
  {
  private:
    std::string _command;
    std::vector<std::string> _args;

  public:
    /**
     * Construct a Request from a line, parsing out the command and the arguments
     * @param line
     */
    explicit Request(const std::string& line);

    Request(std::string command, std::vector<std::string> args);

    [[nodiscard]] std::string command() const;
    std::vector<std::string> args() const;

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] std::string to_line() const;
  };

} // namespace avansync::server