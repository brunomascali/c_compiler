#ifndef C_COMPILER_OPERAND_HPP
#define C_COMPILER_OPERAND_HPP

#include <format>
#include <string>
#include <variant>

#include "ast/ast.hpp"
#include <asm/bit_width.hpp>
#include <ir/ir_generator.hpp>

namespace x86 {
enum class reg {
  // Standard General Purpose
  rax,
  rbx,
  rcx,
  rdx,
  // Index Registers
  rsi,
  rdi,
  // Stack and Base Pointers
  rbp,
  rsp,
  // Numbered Registers
  r8,
  r9,
  r10,
  r11,
  r12,
  r13,
  r14,
  r15
};

// operand ::= imm(int) | register | identifier | stack
struct operand {
  struct immediate {
    int value;
  };
  struct sized_register {
    reg id;
    bit_width width;
  };
  struct identifier {
    std::string name;
  };
  struct stack {
    int32_t offset;
  };
  struct label {
    std::string name;
  };

  std::variant<immediate, sized_register, identifier, stack, label> value;

  explicit operand(const ir::immediate imm) : value(immediate{.value = imm}) {}
  explicit operand(sized_register r) : value(r) {}
  explicit operand(identifier id) : value(id) {}
  explicit operand(stack st) : value(st) {}
  explicit operand(const label &l) : value(label{.name = l.name}) {}

  [[nodiscard]] std::string to_string() const;
};

constexpr auto EAX = operand::sized_register{reg::rax, bit_width::dword};
constexpr auto AL = operand::sized_register{reg::rax, bit_width::byte};
constexpr auto R10D = operand::sized_register{reg::r10, bit_width::dword};
constexpr auto R11D = operand::sized_register{reg::r11, bit_width::dword};
constexpr auto RBP = operand::sized_register{reg::rbp, bit_width::qword};
constexpr auto EDI = operand::sized_register{reg::rdi, bit_width::dword};
constexpr auto ESI = operand::sized_register{reg::rsi, bit_width::dword};
constexpr auto EDX = operand::sized_register{reg::rdx, bit_width::dword};
} // namespace x86

constexpr std::string_view
to_string(const x86::operand::sized_register &register_) {
  const auto &[r, bit_width] = register_;
  using reg = x86::reg;
  if (bit_width == x86::bit_width::dword) {
    switch (r) {
    case reg::rax:
      return "eax";
    case reg::rbx:
      return "ebx";
    case reg::rcx:
      return "ecx";
    case reg::rdx:
      return "edx";
    case reg::rsi:
      return "esi";
    case reg::rdi:
      return "edi";
    case reg::rbp:
      return "ebp";
    case reg::rsp:
      return "esp";
    case reg::r8:
      return "r8d";
    case reg::r9:
      return "r9d";
    case reg::r10:
      return "r10d";
    case reg::r11:
      return "r11d";
    case reg::r12:
      return "r12d";
    case reg::r13:
      return "r13d";
    case reg::r14:
      return "r14d";
    case reg::r15:
      return "r15d";
    default:
      return "unknown";
    }
  }

  if (bit_width == x86::bit_width::byte) {
    switch (r) {
    case reg::rax:
      return "al";
    }
  }

  if (bit_width == x86::bit_width::qword) {
    switch (r) {
    case reg::rbp:
      return "rbp";
    }
  }
  return "unsupported_width";
}

template <> struct std::formatter<x86::operand> {
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
    return std::visit(
        [&](auto &&arg) {
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
          if constexpr (std::is_same_v<T, x86::operand::label>) {
            return std::format_to(ctx.out(), ".{}", arg.name);
          }
        },
        op.value);
  }
};

inline std::string x86::operand::to_string() const {
  return std::format("{}", *this);
}

#endif // C_COMPILER_OPERAND_HPP
