#ifndef C_COMPILER_CMP_HPP
#define C_COMPILER_CMP_HPP

#include <asm/bit_width.hpp>
#include <string>
#include <utility>

#include "instruction.hpp"
#include "operand.hpp"

namespace x86
{
  struct cmp
  {
    cmp(operand a, operand b, const bit_width bw) : a(std::move(a)), b(std::move(b)), width(bw) {}

    [[nodiscard]] std::string emit() const;

    operand a, b;
    bit_width width;
  };
}  // namespace x86

#endif  // C_COMPILER_CMP_HPP
