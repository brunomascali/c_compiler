#ifndef C_COMPILER_JUMP_IF_NOT_ZERO_HPP
#define C_COMPILER_JUMP_IF_NOT_ZERO_HPP

#include <ast/ast.hpp>
#include <ir/defs.hpp>

namespace ir {
struct jump_if_not_zero {
  explicit jump_if_not_zero(identifier target, value condition)
      : target(std::move(target)), condition(std::move(condition)) {}

  identifier target;
  value condition;
};
} // namespace ir

#endif // C_COMPILER_JUMP_IF_NOT_ZERO_HPP
