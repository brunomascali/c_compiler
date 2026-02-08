#ifndef C_COMPILER_X86_CALL_HPP
#define C_COMPILER_X86_CALL_HPP

#include <string>
#include <ir/call.hpp>
#include <asm/operand.hpp>

namespace x86
{
  struct call
  {
    explicit call(const ir::call& instruction) : name(operand::identifier {instruction.function_name}) {}

    [[nodiscard]] std::string emit() const;

    operand name;
  };

}  // namespace x86

#endif  // C_COMPILER_X86_CALL_HPP
