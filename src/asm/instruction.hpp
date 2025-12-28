#ifndef C_COMPILER_INSTRUCTION_HPP
#define C_COMPILER_INSTRUCTION_HPP

#include <ast/ast.hpp>

namespace x86 {
  struct instruction {
    virtual ~instruction() = default;
    [[nodiscard]] virtual std::string to_string() const = 0;
  };
}

#endif //C_COMPILER_INSTRUCTION_HPP