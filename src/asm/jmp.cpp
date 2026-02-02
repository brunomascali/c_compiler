#include <asm/jmp.hpp>
#include <utility>

namespace x86
{
  std::string jmp::emit() const {
    switch (cond) {
      case none:
        return std::format("  jmp {}", target);
      case E:
        return std::format("  je {}", target);
      case NE:
        return std::format("  jne {}", target);
      default:
        std::unreachable();
    }
  }
}  // namespace x86
