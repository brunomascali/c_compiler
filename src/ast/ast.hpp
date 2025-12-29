#ifndef C_COMPILER_AST_HPP
#define C_COMPILER_AST_HPP

#include <string>
#include <variant>
#include <memory>

namespace x86 {
  struct instruction;
}

namespace ast {
  struct unary;
  struct binary;

  using expr = std::variant<int, std::unique_ptr<unary> >;

  struct unary {
    enum class op { complement, negate };

    op operation;
    expr exp;

    unary(const op operation, expr e) : operation(operation), exp(std::move(e)) {
    }
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

    function(std::string n, std::vector<statement> b)
      : name(std::move(n)), body(std::move(b)) {}
  };

  struct program {
    std::vector<function> statements;

    explicit program(std::vector<function> f) : statements(std::move(f)) {}
  };
}

template<class... T>
struct overloaded : T... {
  using T::operator()...;
};

#endif //C_COMPILER_AST_HPP
