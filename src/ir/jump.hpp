#ifndef C_COMPILER_JUMP_HPP
#define C_COMPILER_JUMP_HPP

#include <ast/ast.hpp>
#include <ir/defs.hpp>

namespace ir {
struct jump {
  explicit jump(identifier target) : target(std::move(target)) {}

  identifier target;
};
} // namespace ir

#endif // C_COMPILER_JUMP_HPP
