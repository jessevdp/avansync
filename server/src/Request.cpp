#include "Request.hpp"

#include <iterator>
#include <sstream>
#include <utility>

namespace avansync::server
{

  Request::Request(std::string command, std::vector<std::string> args) :
      _command {std::move(command)}, _args {std::move(args)}
  {}

  Request::Request(const std::string& line)
  {
    std::istringstream iss {line};
    std::vector<std::string> args {std::istream_iterator<std::string> {iss}, std::istream_iterator<std::string> {}};

    std::string command = args[0];
    args.erase(args.begin());

    _command = command;
    _args = args;
  }

  std::string Request::command() const { return _command; }

  std::vector<std::string> Request::args() const { return _args; }

  std::string Request::to_string() const
  {
    std::string s = "Request(command: " + _command;

    if (!_args.empty())
    {
      std::string args;
      for (const auto& arg : _args)
        args += " " + arg;
      s += ", args:" + args;
    }

    s += ")";

    return s;
  }

  std::string Request::to_line() const
  {
    std::string line;
    line += command();
    for (const auto& arg : args())
      line += " " + arg;
    return line;
  }

} // namespace avansync::server