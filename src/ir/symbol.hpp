#ifndef C_COMPILER_SYMBOL_HPP
#define C_COMPILER_SYMBOL_HPP

#include <string>

namespace ir {
  struct symbol {
    explicit symbol(std::string n) : name(std::move(n)) {}

    std::string name;
  };
}

#endif  // C_COMPILER_SYMBOL_HPP
