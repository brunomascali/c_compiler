#ifndef C_COMPILER_ASM_EMITTER_HPP
#define C_COMPILER_ASM_EMITTER_HPP

#include <asm/instruction.hpp>
#include <asm/stack_frame.hpp>
#include <asm/operand.hpp>
#include <ir/defs.hpp>
#include <vector>

namespace x86
{
  class asm_emitter {
   public:
    std::vector<instruction> emit(const ir::instruction &instr);

   private:
    stack_frame m_stack_frame;

    std::vector<instruction> handle_unary(const ir::unary &instruction);

    std::vector<instruction> handle_binary(const ir::binary &instruction);

    std::vector<instruction> handle_return(const ir::return_ &instruction);

    std::vector<instruction> handle_start_function(const ir::function &instruction);

    std::vector<instruction> handle_copy(const ir::copy &instruction);

    std::vector<instruction> handle_jump(const ir::jump &instruction);

    std::vector<instruction> handle_jump_if_zero(const ir::jump_if_zero &instruction);

    std::vector<instruction> handle_jump_if_not_zero(const ir::jump_if_not_zero &instruction);

    std::vector<instruction> handle_label(const ir::label &instruction);

    std::vector<instruction> handle_symbol(const ir::symbol &instruction);

    std::vector<instruction> handle_scope(const ir::begin_scope&);
    std::vector<instruction> handle_scope(const ir::end_scope&);

    // std::vector<instruction> resolve_instructions(const std::vector<instruction>& instructions);

    [[nodiscard]] operand resolve_operand(const ir::value &value);
  };

  // std::string to_string(instruction instruction);
}  // namespace x86


#endif  // C_COMPILER_ASMEMITTER_HPP
