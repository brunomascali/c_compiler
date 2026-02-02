#ifndef C_COMPILER_RET_HPP
#define C_COMPILER_RET_HPP

#include <string>

namespace x86
{
  struct ret
  {
    [[nodiscard]] std::string emit() const;
  };
}  // namespace x86

#endif  // C_COMPILER_RET_HPP
