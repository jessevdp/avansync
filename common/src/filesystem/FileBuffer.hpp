#pragma once

#include <cstdlib>

namespace avansync::filesystem
{

  class FileBuffer
  {
  public:
    virtual ~FileBuffer() = default;

    virtual char* data() = 0;
    virtual size_t size() const = 0;
    virtual void reserve(size_t capacity) = 0;
  };

} // namespace avansync::filesystem
