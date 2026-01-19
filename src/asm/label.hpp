#ifndef C_COMPILER_X86_LABEL_HPP
#define C_COMPILER_X86_LABEL_HPP

#include <utility>

#include "operand.hpp"

namespace x86
{
  struct label
  {
    explicit label(std::string n) : name(std::move(n)) {}

    std::string name;
  };

  [[nodiscard]] inline std::string to_string(const label& l) { return std::format("{}:", l.name); }
}  // namespace x86

#endif  // C_COMPILER_X86_LABEL_HPP
