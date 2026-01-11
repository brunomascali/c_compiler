#include "asm_emitter.hpp"

#include <stack>

namespace x86
{
  template <class... Ts>
  struct overloaded : Ts...
  {
    using Ts::operator()...;
  };

  template <class... Ts>
  overloaded(Ts...) -> overloaded<Ts...>;

  std::vector<instruction_t> asm_emitter::emit(const ir::instruction& instr) {
    return std::visit(
      overloaded{
        [&](const ir::unary_instruction& i) { return handle_unary(i); },
        [&](const ir::binary_instruction& i) { return handle_binary(i); },
        [&](const ir::return_instruction& i) { return handle_return(i); },
        [&](const ir::start_function& i) { return handle_start_function(i); },
      },
      instr);
  }

  std::vector<instruction_t> asm_emitter::handle_unary(const ir::unary_instruction& instruction) {
    const auto src = resolve_operand(instruction.src);
    const auto dst = resolve_operand(instruction.dst);
    const auto mov_instruction = fix_mov_instruction(mov(src, dst));

    std::vector<instruction_t> instructions;
    instructions.insert(instructions.end(), mov_instruction.begin(), mov_instruction.end());
    instructions.emplace_back(unary(instruction.op, dst));

    return instructions;
  }

  std::vector<instruction_t> asm_emitter::handle_binary(const ir::binary_instruction& instruction) {
    std::vector<instruction_t> instructions;

    const auto src1 = resolve_operand(instruction.arg1);
    const auto src2 = resolve_operand(instruction.arg2);
    const auto dst = resolve_operand(instruction.dst);
    const auto op = instruction.op;

    switch (instruction.op) {
      case ast::binary::op::add:
      case ast::binary::op::sub:
      case ast::binary::op::mul:
        instructions.emplace_back(mov(src1, dst));
        for (const auto& inst : fix_imul_instruction(binary(op, src2, dst))) {
          instructions.emplace_back(inst);
        }
        break;
      case ast::binary::op::div:
        instructions.emplace_back(mov(src1, operand(EAX)));
        instructions.emplace_back(mov(src2, operand(ESI)));
        instructions.emplace_back(cdq{});
        instructions.emplace_back(binary(op, src2, operand(ESI)));
        instructions.emplace_back(mov(operand(EAX), dst));
        break;
      case ast::binary::op::rem:
        instructions.emplace_back(mov(src1, operand(EAX)));
        instructions.emplace_back(mov(src2, operand(ESI)));
        instructions.emplace_back(cdq{});
        instructions.emplace_back(binary(op, src2, operand(ESI)));
        instructions.emplace_back(mov(operand(EDX), dst));
        break;
    }
    return instructions;
  }

  std::vector<instruction_t> asm_emitter::handle_return(const ir::return_instruction& instruction) {
    const auto src = resolve_operand(instruction.value);
    const auto eax = operand(EAX);
    const auto rbp = operand(RBP);
    return {mov(src, eax), pop(rbp), ret{}};
  }

  std::vector<instruction_t> asm_emitter::handle_start_function(const ir::start_function& instruction) {
    return {start_function(instruction.name)};
  }

  std::vector<instruction_t> asm_emitter::fix_mov_instruction(const mov& instruction) {
    if (const auto& [src, dst] = instruction;
        std::holds_alternative<operand::stack>(src.value) and std::holds_alternative<operand::stack>(dst.value)) {
      return {mov(src, operand(R10D)), mov(operand(R10D), dst)};
    }

    return {instruction};
  }

  std::vector<instruction_t> asm_emitter::fix_imul_instruction(const binary& instruction) {
    if (const auto& [op, src, dst] = instruction; std::holds_alternative<operand::stack>(dst.value)) {
      return {mov(dst, operand(R11D)), binary(op, src, operand(R11D)), mov(operand(R11D), dst)};
    }

    return {};
  }


  operand asm_emitter::resolve_operand(const ir::value_t& value) {
    return std::visit(overloaded{[&](const ir::immediate& imm) { return operand(imm); },
                                 [&](const ir::identifier& id)
                                 {
                                   const auto offset = operand::stack{.offset = (m_ctx.get_or_create_stack_offset(id))};
                                   return operand(offset);
                                 }},
                      value);
  }

  int32_t codegen_context::get_or_create_stack_offset(const std::string_view ir_var) {
    if (not m_locals.contains(ir_var.data())) {
      m_current_offset -= 4;
      m_locals[ir_var.data()] = m_current_offset;
    }

    return m_locals[ir_var.data()];
  }

  std::string to_string(instruction_t instruction) {
    static constexpr std::string_view prologue =
      "\n  pushq %rbp"
      "\n  movq %rsp, %rbp";

    return std::visit(
      [](auto&& arg) -> std::string
      {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, start_function>) {
          return std::format("  .globl {}\n{}:{}", arg.name, arg.name, prologue);
        }
        else if constexpr (std::is_same_v<T, mov>) {
          return std::format("  movl {}, {}", arg.src, arg.dst);
        }
        else if constexpr (std::is_same_v<T, ret>) {
          return "  ret";
        }
        else if constexpr (std::is_same_v<T, unary>) {
          return arg.to_string();
        }
        else if constexpr (std::is_same_v<T, binary>) {
          return arg.to_string();
        }
        else if constexpr (std::is_same_v<T, pop>) {
          return std::format("  popq {}", arg.src);
        }
        else if constexpr (std::is_same_v<T, cdq>) {
          return "  cltd";
        }
        else {
          return "non-exhaustive visitor (instruction_t -> string)";
        }
      },
      instruction);
  }
}  // namespace x86
