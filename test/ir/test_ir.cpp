#include <iostream>
#include <string>

#include "asm/operand.hpp"
#include "asm/ret.hpp"
#include "gtest/gtest.h"
#include "ir/ir.hpp"

template <typename T, typename Base>
T* cast_and_check(Base* ptr) {
  T* casted = dynamic_cast<T*>(ptr);
  if (!casted) {
    throw std::runtime_error("Failed to cast to expected instruction type");
  }
  return casted;
}

TEST(IR_TESTS, AST_EXPR_TO_IR) {
  auto expr = ast::expr(123);
  const auto ir = ir::from_expr_node(TODO, std::move(expr));

  ASSERT_TRUE(std::holds_alternative<ir::value>(ir[0]));
  const auto value = std::get<ir::value>(ir[0]);
  ASSERT_TRUE(std::holds_alternative<int>(value));
  ASSERT_EQ(std::get<int>(value), 123);
}