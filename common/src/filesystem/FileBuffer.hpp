#pragma once

#include <cstdlib>

namespace avansync
{

  class FileBuffer
  {
  public:
    virtual ~FileBuffer() = default;

    virtual char* data() = 0;
    virtual size_t size() const = 0;
    virtual void reserve(int capacity) = 0;
  };

} // namespace avansync
