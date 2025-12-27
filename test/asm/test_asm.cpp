#include <iostream>
#include <string>
#include <ret.hpp>

#include "function.hpp"
#include "operand.hpp"
#include "gtest/gtest.h"

TEST(ASM_TESTS, TO_STRING)
{
  const x86::ret ret;
  ASSERT_EQ(ret.to_string(), "ret");

  const x86::operand imm("123"), reg(x86::reg::a);
  ASSERT_EQ(imm.to_string(), "123");
  ASSERT_EQ(reg.to_string(), "a");

  const auto func = x86::function_definition("foo", {});
  ASSERT_EQ(func.to_string(), "    .globl foo\nfoo:\n");
}