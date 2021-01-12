#include "VectorFileBuffer.hpp"

namespace avansync
{

  VectorFileBuffer::VectorFileBuffer(int capacity) { _buffer.reserve(capacity); }

  char* VectorFileBuffer::data() { return _buffer.data(); }

  size_t VectorFileBuffer::size() const { return _buffer.capacity(); }

  void VectorFileBuffer::reserve(int capacity) { _buffer.reserve(capacity); }

} // namespace avansync
