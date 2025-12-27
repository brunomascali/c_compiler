#ifndef C_COMPILER_AST_HPP
#define C_COMPILER_AST_HPP

#include <memory>
#include <string>
#include <utility>

struct ast_node {
  virtual ~ast_node() = default;
};

// <exp> ::= <int>
struct expr_node : ast_node {
  std::string value;
  explicit expr_node(std::string val) : value(std::move(val)) {}
};

// <statement> ::= "return" <exp> ";"
struct statement_node : ast_node {
  std::unique_ptr<expr_node> exp;
  explicit statement_node(std::unique_ptr<expr_node> e) : exp(std::move(e)) {}
};

// <function> ::= "int" <identifier> "(" "void" ")" "{" <statement> "}"
struct function_node : ast_node {
  std::string name;
  std::unique_ptr<statement_node> body;

  function_node(std::string n, std::unique_ptr<statement_node> b)
      : name(std::move(n)), body(std::move(b)) {}
};

// <program> ::= <function>
struct program_node : ast_node {
  std::unique_ptr<function_node> function;
  explicit program_node(std::unique_ptr<function_node> f) : function(std::move(f)) {}
};

#endif //C_COMPILER_AST_HPP