#pragma once

#include "filesystem/FileBuffer.hpp"

class TestFileBuffer : public avansync::FileBuffer
{
private:
  int _size;
  char* _data;

public:
  TestFileBuffer(int size, char* data);
  char* data() override;
  size_t size() const override;
  void reserve(int capacity) override;
};