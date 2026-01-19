#ifndef C_COMPILER_RET_HPP
#define C_COMPILER_RET_HPP

#include <string>

namespace x86
{
  struct ret
  {
    [[nodiscard]] std::string to_string() const { return "ret"; }
  };

  [[nodiscard]] inline std::string to_string(const ret&) { return "  ret"; }
}  // namespace x86

#endif  // C_COMPILER_RET_HPP
