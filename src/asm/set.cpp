#include <asm/set.hpp>

namespace x86
{
  std::string set::emit() const { return std::format("  set{} {}", comp_str(comp), dst); }

  [[nodiscard]] inline std::string comp_str(const ast::binary::op comp) {
    switch (comp) {
      case ast::binary::op::eq:
        return "e";
      case ast::binary::op::neq:
        return "ne";
      case ast::binary::op::lt:
        return "l";
      case ast::binary::op::gt:
        return "g";
      case ast::binary::op::le:
        return "le";
      case ast::binary::op::ge:
        return "ge";
      default:
        std::unreachable();
    }
  }
}  // namespace x86
