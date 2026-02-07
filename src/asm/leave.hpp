#ifndef C_COMPILER_LEAVE_HPP
#define C_COMPILER_LEAVE_HPP
#include <string>

namespace x86
{
  struct leave
  {
    [[nodiscard]] std::string emit() const;
  };
}  // namespace x86

#endif //C_COMPILER_LEAVE_HPP
