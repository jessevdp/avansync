#include "FilesystemException.hpp"

namespace avansync
{

  FilesystemException::FilesystemException(const std::string& message) : std::runtime_error(message) {}

} // namespace avansync
