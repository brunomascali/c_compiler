#include <asm/start_function.hpp>

namespace x86
{
  std::string start_function::emit() const {
    constexpr auto prologue =
      "\n  pushq %rbp"
      "\n  movq %rsp, %rbp";
    return std::format("  .globl {}\n{}:{}", name, name, prologue);
  }
}  // namespace x86
