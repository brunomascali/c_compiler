#include <asm/unary.hpp>
#include <utility>

namespace x86 {

  std::string unary::emit() const {
    switch (unary_operator) {
      case ast::unary::op::not_:
        return std::format("  notl {}", dst);
      case ast::unary::op::negate:
        return std::format("  negl {}", dst);
      default:
        std::unreachable();
    }
  }

}  // namespace x86
