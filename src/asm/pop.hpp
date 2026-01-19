#ifndef C_COMPILER_POP_HPP
#define C_COMPILER_POP_HPP

#include "operand.hpp"

namespace x86
{
  struct pop
  {
    explicit pop(operand s) : src(std::move(s)) {}

    operand src;
  };

  [[nodiscard]] inline std::string to_string(const pop& p) { return std::format("  popq {}", p.src); }

}  // namespace x86

#endif  // C_COMPILER_POP_HPP
