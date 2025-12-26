#ifndef C_COMPILER_TOKEN_HPP
#define C_COMPILER_TOKEN_HPP

#include <string>

class token
{
public:
  enum class token_kind {
    // Keywords
    int_kw, void_kw, return_kw,
    // non-fixed tokens
    identifier, number,
    // punctuation
    paren_open, paren_close,
    brace_open, brace_close,
    semicolon,
  };

  explicit token(const token_kind k, std::string lexeme = "") : m_kind(k), m_lexeme(std::move(lexeme)) {}

  token_kind kind() const {
    return m_kind;
  }

  std::string lexeme() const {
    return m_lexeme;
  }

private:
  token_kind m_kind;
  std::string m_lexeme;
};


#endif //C_COMPILER_TOKEN_HPP