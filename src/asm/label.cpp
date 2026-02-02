#include <asm/label.hpp>

namespace x86
{
  std::string label::emit() const {
    return std::format("{}:", value);
  }
}  // namespace x86
