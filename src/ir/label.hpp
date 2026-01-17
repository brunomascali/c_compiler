#ifndef C_COMPILER_LABEL_HPP
#define C_COMPILER_LABEL_HPP

#include <ast/ast.hpp>
#include <ir/defs.hpp>

namespace ir {
struct label {
  explicit label(identifier name) : name(std::move(name)) {}

  identifier name;
};
} // namespace ir

#endif // C_COMPILER_LABEL_HPP
