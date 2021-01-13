#include "TestFileBuffer.hpp"

TestFileBuffer::TestFileBuffer(int size, char* data) : _size {size}, _data {data} {}

char* TestFileBuffer::data()
{
  return _data;
}

size_t TestFileBuffer::size() const
{
  return _size;
}

void TestFileBuffer::reserve(int capacity)
{
  // do nothing
}