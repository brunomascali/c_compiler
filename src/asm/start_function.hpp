#ifndef C_COMPILER_START_FUNCTION_HPP
#define C_COMPILER_START_ FUNCTION_HPP

#include <memory>
#include <string>

namespace x86
{
  struct start_function
  {
    std::string name;

    explicit start_function(std::string n) : name(std::move(n)) {}
  };

  [[nodiscard]] inline std::string to_string(const start_function& f) {
    constexpr std::string_view prologue =
      "\n  pushq %rbp"
      "\n  movq %rsp, %rbp";
    return std::format("  .globl {}\n{}:{}", f.name, f.name, prologue);
  }
}  // namespace x86

#endif
