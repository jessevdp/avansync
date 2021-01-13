#include "TestDirectoryEntry.hpp"

bool TestDirectoryEntry::is_regular_file() const
{
  return true;
}

bool TestDirectoryEntry::is_directory() const
{
  return false;
}

bool TestDirectoryEntry::is_symlink() const
{
  return false;
}

std::string TestDirectoryEntry::name() const
{
  return "fake-file-name";
}

std::string TestDirectoryEntry::relative_path() const
{
  return "./fake-file-name";
}

unsigned long TestDirectoryEntry::file_size() const
{
  return 10;
}
std::string TestDirectoryEntry::formatted_modification_timestamp() const
{
  return "fake modification timestamp";
}
