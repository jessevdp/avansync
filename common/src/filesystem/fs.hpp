#pragma once

#ifdef CXX_FILESYSTEM_IS_EXPERIMENTAL
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace std::experimental::filesystem
{
  path relative(const path& subject_path, const path& base_path)
  {
    // 1. convert p and base to absolute paths
    auto p = absolute(subject_path);
    auto base = absolute(base_path);

    // 2. find first mismatch and shared root path
    auto mismatched = std::mismatch(p.begin(), p.end(), base.begin(), base.end());

    // 3. if no mismatch return "."
    if (mismatched.first == p.end() && mismatched.second == base.end()) return ".";

    auto it_p = mismatched.first;
    auto it_base = mismatched.second;

    path ret;

    // 4. iterate abase to the shared root and append "../"
    for (; it_base != base.end(); ++it_base)
      ret /= "..";

    // 5. iterate from the shared root to the p and append its parts
    for (; it_p != p.end(); ++it_p)
      ret /= *it_p;

    return ret;
  }
}

#else
#include <filesystem>
namespace fs = std::filesystem;
#endif