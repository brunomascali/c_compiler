#ifndef C_COMPILER_OPERAND_HPP
#define C_COMPILER_OPERAND_HPP

#include <format>
#include <string>
#include <variant>

#include <ir/ir.hpp>
#include "ast/ast.hpp"

namespace x86 {
  enum class reg {
    // Standard General Purpose
    rax, rbx, rcx, rdx,
    // Index Registers
    rsi, rdi,
    // Stack and Base Pointers
    rbp, rsp,
    // Numbered Registers
    r8, r9, r10, r11,
    r12, r13, r14, r15
  };

  enum class bit_width {
    BYTE, WORD, DWORD, QWORD
  };

  // operand ::= imm(int) | register | identifier | stack
  struct operand {
    struct immediate { int value; };
    struct sized_register {
      reg id;
      bit_width width;
    };
    using identifier = std::string;
    struct stack { int32_t offset; };

    std::variant<immediate, sized_register, identifier, stack> value;

    explicit operand(const ir::immediate imm) : value(immediate{.value=imm}) {}
    explicit operand(sized_register r) : value(r) {}
    explicit operand(identifier id) : value(id) {}
    explicit operand(stack st) : value(st) {}

    // explicit

    [[nodiscard]] std::string to_string() const;
  };

  constexpr auto EAX = operand::sized_register{reg::rax, bit_width::DWORD};
  constexpr auto R10D = operand::sized_register{reg::r10, bit_width::DWORD};
  constexpr auto R11D = operand::sized_register{reg::r11, bit_width::DWORD};
  constexpr auto RBP = operand::sized_register{reg::rbp, bit_width::QWORD};
  constexpr auto EDI = operand::sized_register{reg::rdi, bit_width::DWORD};
  constexpr auto ESI = operand::sized_register{reg::rsi, bit_width::DWORD};
  constexpr auto EDX = operand::sized_register{reg::rdx, bit_width::DWORD};
}


constexpr std::string_view to_string(const x86::operand::sized_register &register_) {
  const auto &[r, bit_width] = register_;
  using reg = x86::reg;
  if (bit_width == x86::bit_width::DWORD) {
    switch (r) {
      case reg::rax: return "eax";
      case reg::rbx: return "ebx";
      case reg::rcx: return "ecx";
      case reg::rdx: return "edx";
      case reg::rsi: return "esi";
      case reg::rdi: return "edi";
      case reg::rbp: return "ebp";
      case reg::rsp: return "esp";
      case reg::r8: return "r8d";
      case reg::r9: return "r9d";
      case reg::r10: return "r10d";
      case reg::r11: return "r11d";
      case reg::r12: return "r12d";
      case reg::r13: return "r13d";
      case reg::r14: return "r14d";
      case reg::r15: return "r15d";
      default: return "unknown";
    }
  }
  switch (r) {
    case reg::rax: return "rax";
    case reg::rbx: return "rbx";
    case reg::rcx: return "rcx";
    case reg::rdx: return "rdx";
    case reg::rsi: return "rsi";
    case reg::rdi: return "rdi";
    case reg::rbp: return "rbp";
    case reg::rsp: return "rsp";
    case reg::r8: return "r8";
    case reg::r9: return "r9";
    case reg::r10: return "r10";
    case reg::r11: return "r11";
    case reg::r12: return "r12";
    case reg::r13: return "r13";
    case reg::r14: return "r14";
    case reg::r15: return "r15";
    default: return "unknown";
  }
}

template<>
struct std::formatter<x86::operand> {
  int bit_width = 64;

  constexpr auto parse(std::format_parse_context &ctx) {
    auto it = ctx.begin();
    if (it != ctx.end() && *it != '}') {
      if (*it == '3') {
        bit_width = 32;
        it += 2;
      } else if (*it == '6') {
        bit_width = 64;
        it += 2;
      }
    }
    return it;
    return ctx.begin();
  }

  auto format(const x86::operand &op, std::format_context &ctx) const {
    return std::visit([&](auto &&arg) {
      using T = std::decay_t<decltype(arg)>;
      if constexpr (std::is_same_v<T, x86::operand::immediate>) {
        return std::format_to(ctx.out(), "${}", arg.value);
      }
      if constexpr (std::is_same_v<T, x86::operand::sized_register>) {
        return std::format_to(ctx.out(), "%{}", ::to_string(arg));
      }
      if constexpr (std::is_same_v<T, x86::operand::identifier>) {
        return std::format_to(ctx.out(), "????");
      }
      if constexpr (std::is_same_v<T, x86::operand::stack>) {
        return std::format_to(ctx.out(), "{}(%rbp)", arg.offset);
      }
    }, op.value);
  }
};

inline std::string x86::operand::to_string() const {
  return std::format("{}", *this);
}

#endif //C_COMPILER_OPERAND_HPP
