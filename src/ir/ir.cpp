#include "ir.hpp"

namespace ir {
  value from_expr_node(context &ctx, ast::expr exp) {
    return std::visit([&](auto &&arg) {
      using T = std::decay_t<decltype(arg)>;

      if constexpr (std::is_same_v<T, int>) {
        return value(arg);
      }
      if constexpr (std::is_same_v<T, ast::unary>) {
        auto src = from_expr_node(ctx, std::move(*arg.exp));
        value dst{"TMP"};
        ctx.emplace_back(unary_instruction{arg.operation, src, dst});
        return value("TMP");
      }
    }, exp);
  }

  void from_statement_node(context &ctx, ast::statement stmt) {
    std::visit([&](auto &&arg) {
      using T = std::decay_t<decltype(arg)>;

      if constexpr (std::is_same_v<T, ast::return_stmt>) {
        auto src = from_expr_node(ctx, std::move(arg.expression));
        ctx.emplace_back(return_instruction(std::move(src)));
      }
    }, stmt);
  }
}
