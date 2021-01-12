#pragma once

#include "FileBuffer.hpp"

#include <vector>

namespace avansync
{

  class VectorFileBuffer : public FileBuffer
  {
  private:
    std::vector<char> _buffer {};

  public:
    VectorFileBuffer() = default;
    explicit VectorFileBuffer(int capacity);

    char* data() override;
    [[nodiscard]] size_t size() const override;
    void reserve(int capacity) override;
  };

} // namespace avansync
