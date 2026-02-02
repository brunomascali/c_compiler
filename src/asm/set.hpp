#ifndef C_COMPILER_SET_HPP
#define C_COMPILER_SET_HPP

#include <utility>

#include "operand.hpp"

namespace x86
{
  struct set
  {
    set(const ast::binary::op c, operand o) : comp(c), dst(std::move(o)) {}

    [[nodiscard]] std::string emit() const;

    ast::binary::op comp;
    operand dst;
  };

  [[nodiscard]] inline std::string comp_str(ast::binary::op comp);
}  // namespace x86

#endif  // C_COMPILER_SET_HPP
