#include <iostream>
#include <string>

#include "asm/start_function.hpp"
#include "asm/ret.hpp"
#include "gtest/gtest.h"

template <typename T, typename Base>
T* cast_and_check(Base* ptr) {
  T* casted = dynamic_cast<T*>(ptr);
  if (!casted) {
    throw std::runtime_error("Failed to cast to expected instruction type");
  }
  return casted;
}

TEST(ASM_TESTS, TO_STRING) {
  const x86::ret ret;
  ASSERT_EQ(ret.to_string(), "ret");

  const x86::operand imm("123"), reg(x86::reg::eax);
  ASSERT_EQ(imm.to_string(), "123");
  ASSERT_EQ(reg.to_string(), "eax");

  const auto func = x86::function_definition("foo", {});
  ASSERT_EQ(func.to_string(), "    .globl foo\nfoo:\n");
}

TEST(ASM_TESTS, EXPR_TO_ASM) {
  const auto expr = std::make_unique<expr_node>("123");
  const auto x = ast_to_operand(expr);
  ASSERT_EQ(std::get<std::string>(x.value), "123");
}

TEST(ASM_TESTS, RETURN_TO_ASM) {
  const auto ast_ret = std::make_unique<statement_node>(
    std::make_unique<expr_node>("123")
  );

  const auto asm_list = x86::ast_to_asm(ast_ret);

  ASSERT_EQ(asm_list.size(), 2);

  const auto* mov = cast_and_check<x86::mov>(asm_list[0].get());
  const auto* ret = cast_and_check<x86::ret>(asm_list[1].get());

  EXPECT_NO_THROW(std::get<std::string>(mov->src->value));
  EXPECT_NO_THROW(std::get<x86::reg>(mov->dst->value));
  const auto lit = std::get<std::string>(mov->src->value);
  const auto reg = std::get<x86::reg>(mov->dst->value);
  EXPECT_EQ(lit, "123");
  EXPECT_EQ(reg, x86::reg::eax);
}