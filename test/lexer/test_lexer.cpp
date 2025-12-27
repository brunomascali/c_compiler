#include <iostream>

#include "lexer.hpp"
#include "gtest/gtest.h"

TEST(LEXER_TESTS, MINIMAL_PROGRAM)
{
  const std::string source_code = "int main(void) { return 0; }";
  const auto tokens = lexer(source_code).tokenize();

  // 10 Tokens: [int] [main] [(] [void] [)] [{] [return] [0] [;] [}]
  ASSERT_EQ(tokens.size(), 10);

  // int main(void)
  EXPECT_EQ(tokens[0].kind(), token::token_kind::int_kw);
  EXPECT_EQ(tokens[1].kind(), token::token_kind::identifier);
  EXPECT_EQ(tokens[1].lexeme(), "main");
  EXPECT_EQ(tokens[2].kind(), token::token_kind::paren_open);
  EXPECT_EQ(tokens[3].kind(), token::token_kind::void_kw);
  EXPECT_EQ(tokens[4].kind(), token::token_kind::paren_close);

  // { return 0; }
  EXPECT_EQ(tokens[5].kind(), token::token_kind::brace_open);
  EXPECT_EQ(tokens[6].kind(), token::token_kind::return_kw);
  EXPECT_EQ(tokens[7].kind(), token::token_kind::number);
  EXPECT_EQ(tokens[7].lexeme(), "0");
  EXPECT_EQ(tokens[8].kind(), token::token_kind::semicolon);
  EXPECT_EQ(tokens[9].kind(), token::token_kind::brace_close);
}