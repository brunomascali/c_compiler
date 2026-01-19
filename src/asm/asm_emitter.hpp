#ifndef C_COMPILER_ASM_EMITTER_HPP
#define C_COMPILER_ASM_EMITTER_HPP

#include <asm/codegen_context.hpp>
#include <asm/instruction.hpp>
#include <vector>
#include <initializer_list>

namespace x86
{
  class asm_emitter {
   public:
    explicit asm_emitter(codegen_context &ctx) : m_ctx(ctx) {}

    std::vector<instruction_t> emit(const ir::instruction &instr);

   private:
    codegen_context &m_ctx;

    std::vector<instruction_t> handle_unary(const ir::unary &instruction);

    std::vector<instruction_t> handle_binary(const ir::binary &instruction);

    std::vector<instruction_t> handle_return(const ir::return_ &instruction);

    std::vector<instruction_t> handle_start_function(const ir::start_function &instruction);

    std::vector<instruction_t> handle_copy(const ir::copy &instruction);

    std::vector<instruction_t> handle_jump(const ir::jump &instruction);

    std::vector<instruction_t> handle_jump_if_zero(const ir::jump_if_zero &instruction);

    std::vector<instruction_t> handle_jump_if_not_zero(const ir::jump_if_not_zero &instruction);

    std::vector<instruction_t> handle_label(const ir::label &instruction);

    std::vector<instruction_t> resolve_instructions(const std::initializer_list<instruction_t> &instructions) {
      std::vector<instruction_t> resolved_instructions;
      for (const auto &inst : instructions) {
        std::visit(
          [&](auto &&arg)
          {
            if constexpr (requires { legalize(arg); }) {
              for (const auto &legalized_instruction : legalize(arg)) {
                resolved_instructions.emplace_back(legalized_instruction);
              }
            }
            else {
              resolved_instructions.emplace_back(inst);
            }
          },
          inst);
      }

      return resolved_instructions;
    }

    std::vector<instruction_t> resolve_imul_operands(const binary &instruction);

    std::vector<instruction_t> resolve_cmp_operands(const cmp &instruction);

    [[nodiscard]] operand resolve_operand(const ir::value &value) const;
  };

  std::string to_string(instruction_t instruction);
}  // namespace x86


#endif  // C_COMPILER_ASMEMITTER_HPP
