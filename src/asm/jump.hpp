#ifndef C_COMPILER_x86_JUMP_HPP
#define C_COMPILER_x86_JUMP_HPP

#include "operand.hpp"

namespace x86 {
struct jump {
  enum condition { none };

  jump(condition c, std::string t) : cond(std::move(c)), target(std::move(t)) {}

  condition cond;
  std::string target;
};
} // namespace x86

#endif // C_COMPILER_x86_JUMP_HPP
