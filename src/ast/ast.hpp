#ifndef C_COMPILER_AST_HPP
#define C_COMPILER_AST_HPP

#include <string>
#include <variant>

namespace x86 {
  struct instruction;
}

namespace ast {
  struct unary;
  struct binary;

  using expr = std::variant<
    int>;

  struct unary {
    std::string op;
    expr target;
  };

  struct binary {
    expr left;
    std::string op;
    expr right;
  };

  struct return_stmt {
    expr expression;
  };

  using statement = std::variant<return_stmt>;

  struct function {
    std::string name;
    std::vector<statement> body;
  };

  struct program {
    std::vector<function> statements;
  };
}

template<class... T>
struct overloaded : T... {
  using T::operator()...;
};

#endif //C_COMPILER_AST_HPP
