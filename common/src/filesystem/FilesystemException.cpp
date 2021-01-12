#include "FilesystemException.hpp"

namespace avansync::filesystem
{

  FilesystemException::FilesystemException(const std::string& message) : std::runtime_error(message) {}

} // namespace avansync::filesystem
