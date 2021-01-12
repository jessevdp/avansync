#pragma once

#include "FileBuffer.hpp"

#include <vector>

namespace avansync::filesystem
{

  class VectorFileBuffer : public FileBuffer
  {
  private:
    std::vector<char> _buffer {};

  public:
    VectorFileBuffer() = default;
    explicit VectorFileBuffer(size_t capacity);

    char* data() override;
    [[nodiscard]] size_t size() const override;
    void reserve(size_t capacity) override;
  };

} // namespace avansync::filesystem
