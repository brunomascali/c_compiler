#ifndef C_COMPILER_COPY_HPP
#define C_COMPILER_COPY_HPP

#include <ast/ast.hpp>
#include <ir/defs.hpp>

namespace ir {
struct copy {
  copy(value src, value dst) : src(std::move(src)), dst(std::move(dst)) {}

  value src, dst;
};
} // namespace ir

#endif // C_COMPILER_COPY_HPP
