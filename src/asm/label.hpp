#ifndef C_COMPILER_X86_LABEL_HPP
#define C_COMPILER_X86_LABEL_HPP

#include <utility>

#include "operand.hpp"

namespace x86
{
  struct label
  {
    explicit label(std::string n) : value(std::move(n)) {}

    [[nodiscard]] std::string emit() const;

    std::string value;
  };
}  // namespace x86

#endif  // C_COMPILER_X86_LABEL_HPP
