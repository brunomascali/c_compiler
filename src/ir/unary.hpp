#ifndef C_COMPILER_UNARY_HPP
#define C_COMPILER_UNARY_HPP

#include <ir/defs.hpp>

namespace ir {
struct unary {
  unary(const ast::unary::op op, value src, value dst)
      : op(op), src(std::move(src)), dst(std::move(dst)) {}

  ast::unary::op op;
  value src, dst;
};
} // namespace ir

#endif // C_COMPILER_UNARY_HPP
