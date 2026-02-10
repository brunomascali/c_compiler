#ifndef C_COMPILER_AST_BLOCK_ITEM_HPP
#define C_COMPILER_AST_BLOCK_ITEM_HPP

#include <variant>
#include <ast/ast_fwd.hpp>
#include <ast/statement/declaration.hpp>

namespace ast {
  struct block_item : std::variant<Box<statement>, Box<declaration>>
  {
    using variant::variant;
  };
}

#endif