#ifndef C_COMPILER_x86_JUMP_HPP
#define C_COMPILER_x86_JUMP_HPP

#include "operand.hpp"

namespace x86
{
  struct jmp
  {
    enum condition
    {
      none,
      E,
      NE
    };

    jmp(const condition c, std::string t) : cond(c), target(std::move(t)) {}

    [[nodiscard]] std::string emit() const;

    condition cond;
    std::string target;
  };
}  // namespace x86

#endif  // C_COMPILER_x86_JUMP_HPP
