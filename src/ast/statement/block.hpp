#ifndef C_COMPILER_AST_BLOCK_HPP
#define C_COMPILER_AST_BLOCK_HPP

#include <vector>
#include <ast/ast_fwd.hpp>
#include <ast/statement/block_item.hpp>

namespace ast {
  struct block
  {
    std::vector<block_item> items;
  };
}

#endif