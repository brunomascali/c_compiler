#ifndef C_COMPILER_DEFS_HPP
#define C_COMPILER_DEFS_HPP

#include <variant>
#include <ir/unary.hpp>
#include <ir/binary.hpp>
#include <ir/return.hpp>
#include <ir/function.hpp>
#include <ir/copy.hpp>
#include <ir/jump.hpp>
#include <ir/jump_if_not_zero.hpp>
#include <ir/jump_if_zero.hpp>
#include <ir/label.hpp>

namespace ir
{
  struct instruction : std::variant<unary, binary, return_, function, copy, jump, jump_if_not_zero, jump_if_zero, label>
  {
  };
}  // namespace ir

#endif  // C_COMPILER_DEFS_HPP
