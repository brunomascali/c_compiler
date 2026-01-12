#ifndef C_COMPILER_BINARY_HPP
#define C_COMPILER_BINARY_HPP

#include <ast/ast.hpp>
#include <ir/defs.hpp>

namespace ir {
struct binary {
  binary(const ast::binary::op op, value arg1, value arg2,
                     value dst)
      : op(op), arg1(std::move(arg1)), arg2(std::move(arg2)),
        dst(std::move(dst)) {}

  ast::binary::op op;
  value arg1, arg2, dst;
};
} // namespace ir

#endif // C_COMPILER_BINARY_HPP
