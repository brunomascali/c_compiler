#ifndef C_COMPILER_FUNCTION_HPP
#define C_COMPILER_FUNCTION_HPP

#include <memory>
#include <string>

namespace x86 {
  struct start_function {
    std::string name;

    explicit start_function(std::string n) : name(std::move(n)) {}

    [[nodiscard]] std::string to_string() const;
  };
}

#endif //C_COMPILER_FUNCTION_HPP