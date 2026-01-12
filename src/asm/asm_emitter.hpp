#ifndef C_COMPILER_ASM_EMITTER_HPP
#define C_COMPILER_ASM_EMITTER_HPP

#include <map>
#include <vector>

#include "binary.hpp"
#include "ret.hpp"
#include "start_function.hpp"
#include "mov.hpp"
#include "unary.hpp"
#include "pop.hpp"
#include "cdq.hpp"
#include <ir/unary.hpp>

namespace x86 {
  using instruction_t = std::variant<start_function, mov, ret, unary, binary, pop, cdq>;

  class codegen_context;

  class asm_emitter {
  public:
    explicit asm_emitter(codegen_context &ctx) : m_ctx(ctx) {
    }

    std::vector<instruction_t> emit(const ir::instruction &instr);

  private:
    codegen_context &m_ctx;

    std::vector<instruction_t> handle_unary(const ir::unary &instruction);

    std::vector<instruction_t> handle_binary(const ir::binary &instruction);

    std::vector<instruction_t> handle_return(const ir::return_ &instruction);

    std::vector<instruction_t> handle_start_function(const ir::start_function &instruction);

    std::vector<instruction_t> fix_imul_instruction(const binary& instruction);

    std::vector<instruction_t> fix_mov_instruction(const mov &instruction);

    operand resolve_operand(const ir::value &value);
  };

  class codegen_context {
  public:
    int32_t get_or_create_stack_offset(std::string_view ir_var);

    [[nodiscard]] int32_t total_stack_usage() const;

  private:
    std::map<std::string, int32_t> m_locals;
    int32_t m_current_offset{0};
  };

  std::string to_string(instruction_t instruction);
}


#endif //C_COMPILER_ASMEMITTER_HPP
