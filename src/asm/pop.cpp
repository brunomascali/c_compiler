#include <asm/pop.hpp>

namespace x86
{
  std::string pop::emit() const { return std::format("popq {}", src); }
}  // namespace x86
