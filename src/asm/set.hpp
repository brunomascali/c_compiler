#ifndef C_COMPILER_SET_HPP
#define C_COMPILER_SET_HPP

#include <utility>

#include "operand.hpp"

namespace x86 {
struct set {
  set(const ast::binary::op c, operand o) : comp(c), dst(std::move(o)) {}

  [[nodiscard]] static std::string comp_str(const ast::binary::op comp) {
    switch (comp) {
    case ast::binary::op::eq: return "e";
    case ast::binary::op::neq: return "ne";
    case ast::binary::op::lt: return "l";
    case ast::binary::op::gt: return "g";
    case ast::binary::op::le: return "le";
    case ast::binary::op::ge: return "ge";
    default: throw std::invalid_argument("INVALID COMPARISON OPERATOR");
    }
  }

  [[nodiscard]] std::string to_string() const {
    return std::format("  set{} {}", comp_str(comp), dst);
  }

  ast::binary::op comp;
  operand dst;
};
} // namespace ir

#endif // C_COMPILER_SET_HPP
