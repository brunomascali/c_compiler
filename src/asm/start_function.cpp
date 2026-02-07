#include <asm/start_function.hpp>

namespace x86
{
  std::string start_function::emit() const {
    constexpr auto prologue_main =
      "\n  pushq %rbp"
      "\n  movq %rsp, %rbp"
      "\n  subq $16, %rsp";

    constexpr auto prologue =
      "\n  pushq %rbp"
      "\n  movq %rsp, %rbp";

    return std::format("  .globl {}\n{}:{}", name, name,  name == "main" ? prologue_main : prologue);
  }
}  // namespace x86
