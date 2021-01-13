#pragma once

#ifdef CXX_FILESYSTEM_IS_EXPERIMENTAL
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace std::experimental::filesystem
{
  path relative(const path& subject_path, const path& base_path);
}

#else
#include <filesystem>
namespace fs = std::filesystem;
#endif