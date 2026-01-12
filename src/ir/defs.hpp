#ifndef C_COMPILER_DEFS_HPP
#define C_COMPILER_DEFS_HPP

namespace ir {
using immediate = int;
using identifier = std::string;

struct value {
  explicit value(immediate imm) : inner (imm) {}
  explicit value(std::string str) : inner(str) {}
  std::variant<immediate, identifier> inner;
};
} // namespace ir

#endif // C_COMPILER_DEFS_HPP
