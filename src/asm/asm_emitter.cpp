#include "asm_emitter.hpp"

#include <asm/instruction.hpp>
#include <iostream>

namespace x86
{

  template <class... Ts>
  struct overloaded : Ts...
  {
    using Ts::operator()...;
  };

  template <class... Ts>
  overloaded(Ts...) -> overloaded<Ts...>;

  std::vector<instruction_t> asm_emitter::emit(const ir::instruction &instr) {
    const auto instructions = std::visit(
      overloaded{
        [&](const ir::unary &i) { return handle_unary(i); },
        [&](const ir::binary &i) { return handle_binary(i); },
        [&](const ir::return_ &i) { return handle_return(i); },
        [&](const ir::function &i) { return handle_start_function(i); },
        [&](const ir::copy &i) { return handle_copy(i); },
        [&](const ir::jump &i) { return handle_jump(i); },
        [&](const ir::jump_if_zero &i) { return handle_jump_if_zero(i); },
        [&](const ir::jump_if_not_zero &i) { return handle_jump_if_not_zero(i); },
        [&](const ir::label &i) { return handle_label(i); },
        [&](const ir::symbol &i) { return handle_symbol(i); },
        [&](const ir::begin_scope &i) { return handle_scope(i); },
        [&](const ir::end_scope &i) { return handle_scope(i); },
      },
      instr);

    return resolve_instructions(instructions);
  }

  std::vector<instruction_t> asm_emitter::handle_unary(const ir::unary &instruction) {
    const auto src = resolve_operand(instruction.src);
    const auto dst = resolve_operand(instruction.dst);

    return {mov(src, dst), unary(instruction.op, dst)};
  }

  std::vector<instruction_t> asm_emitter::handle_binary(const ir::binary &instruction) {
    const auto src1 = resolve_operand(instruction.arg1);
    const auto src2 = resolve_operand(instruction.arg2);
    const auto dst = resolve_operand(instruction.dst);
    const auto op = instruction.op;

    switch (instruction.op) {
      case ast::binary::op::add:
      case ast::binary::op::sub:
      case ast::binary::op::mul:
        return {mov(src1, dst), binary(op, src2, dst)};
      case ast::binary::op::div:
        return {mov(src1, operand(EAX)), mov(src2, operand(ESI)), cdq{}, binary(op, src2, operand(ESI)),
                mov(operand(EAX), dst)};

      case ast::binary::op::rem:
        return {mov(src1, operand(EAX)), mov(src2, operand(ESI)), cdq{}, binary(op, src2, operand(ESI)),
                mov(operand(EDX), dst)};

      case ast::binary::op::eq:
      case ast::binary::op::neq:
      case ast::binary::op::lt:
      case ast::binary::op::le:
      case ast::binary::op::gt:
      case ast::binary::op::ge:
        return {
          cmp(src2, src1, bit_width::dword),
          set(instruction.op, operand(AL)),
          mov(operand(AL), dst, bit_width::byte),
        };
    }
  }

  std::vector<instruction_t> asm_emitter::handle_return(const ir::return_ &instruction) {
    const auto src = resolve_operand(instruction.val);

    return {
      mov(src, EAX),
      pop(RBP),
      ret{},
    };
  }

  std::vector<instruction_t> asm_emitter::handle_start_function(const ir::function &instruction) {
    return {start_function(instruction.name)};
  }

  std::vector<instruction_t> asm_emitter::handle_copy(const ir::copy &instruction) {
    const auto src = resolve_operand(instruction.src);
    const auto dst = resolve_operand(instruction.dst);

    return {mov(src, dst)};
  }

  std::vector<instruction_t> asm_emitter::handle_jump(const ir::jump &instruction) {
    using cc = jmp::condition;
    return {jmp(cc::none, instruction.target)};
  }

  std::vector<instruction_t> asm_emitter::handle_jump_if_zero(const ir::jump_if_zero &instruction) {
    return {cmp(0, resolve_operand(instruction.condition), bit_width::byte),
            jmp(jmp::condition::E, instruction.target)};
  }

  std::vector<instruction_t> asm_emitter::handle_jump_if_not_zero(const ir::jump_if_not_zero &instruction) {
    return {cmp(0, resolve_operand(instruction.condition), bit_width::byte),
            jmp(jmp::condition::NE, instruction.target)};
  }

  std::vector<instruction_t> asm_emitter::handle_label(const ir::label &instruction) {
    return {label(instruction.name)};
  }

  std::vector<instruction_t> asm_emitter::handle_symbol(const ir::symbol &instruction) {
    m_stack_frame.register_symbol(instruction.name);
    return {};
  }

  std::vector<instruction_t> asm_emitter::handle_scope(const ir::begin_scope &instruction) {
    m_stack_frame.push_scope();
    return {};
  }

  std::vector<instruction_t> asm_emitter::handle_scope(const ir::end_scope &instruction) {
    m_stack_frame.pop_scope();
    return {};
  }

  std::vector<instruction_t> asm_emitter::resolve_instructions(const std::vector<instruction_t> &instructions) {
    {
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
  }

  operand asm_emitter::resolve_operand(const ir::value &value) {
    return std::visit(overloaded{[&](const ir::immediate &imm) { return operand(imm); },
                                 [&](const ir::identifier &id)
                                 {
                                   const auto offset = m_stack_frame.resolve_variable_offset(id);
                                   return operand(operand::stack{.offset = offset});
                                 },
                                 [&](const ir::label &l) { return operand(operand::label{.name = l.name}); }},
                      value);
  }

  std::string to_string(instruction_t instruction) {
    return std::visit(
      [index = instruction.index()](auto &&arg) -> std::string
      {
        if constexpr (requires { x86::to_string(arg); }) {
          return x86::to_string(arg);
        }
        else {
          return std::format("variant index {} does not support to_string()", index);
        }
      },
      instruction);
  }
}  // namespace x86
