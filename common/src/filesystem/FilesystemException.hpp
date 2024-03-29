#pragma once

#include <stdexcept>
#include <string>

namespace avansync
{

  class FilesystemException : public std::runtime_error
  {
  public:
    explicit FilesystemException(const std::string& message);
  };

} // namespace avansync
