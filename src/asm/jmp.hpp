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

    jmp(condition c, std::string t) : cond(c), target(std::move(t)) {}

    condition cond;
    std::string target;
  };

  [[nodiscard]] inline std::string to_string(const jmp& jmp) {
    using cond = jmp::condition;
    switch (jmp.cond) {
      case cond::none: return std::format("  jmp {}", jmp.target);
      case cond::E: return std::format("  je {}", jmp.target);
      case cond::NE: return std::format("  jne {}", jmp.target);
    }
    throw std::invalid_argument("jmp condition not implementedu");
  }
}  // namespace x86

#endif  // C_COMPILER_x86_JUMP_HPP
