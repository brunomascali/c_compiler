#ifndef C_COMPILER_TOKEN_HPP
#define C_COMPILER_TOKEN_HPP

#include <format>
#include <string>
#include <vector>

class token {
 public:
  enum class token_kind
  {
    // Keywords
    int_kw,
    void_kw,
    return_kw,
    // non-fixed tokens
    identifier,
    number,
    // punctuation
    paren_open,
    paren_close,
    brace_open,
    brace_close,
    semicolon,
    hyphen,
    tilde,
    plus,
    asterisk,
    slash,
    percent,
  };

  explicit token(const token_kind k, std::string lexeme = "") : m_kind(k), m_lexeme(std::move(lexeme)) {}

  [[nodiscard]] token_kind kind() const { return m_kind; }

  [[nodiscard]] std::string lexeme() const { return m_lexeme; }

 private:
  token_kind m_kind;
  std::string m_lexeme;
};

inline std::optional<int> precedence(const token::token_kind kind) {
  using tk = token::token_kind;
  switch (kind) {
    case tk::asterisk:
    case tk::slash:
    case tk::percent:
      return 50;
    case tk::int_kw:
    case tk::hyphen:
      return 45;
    default:
      return std::nullopt;
  }
}

template <>
struct std::formatter<token::token_kind>
{
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(token::token_kind k, std::format_context &ctx) const {
    std::string_view name = "unknown";
    switch (k) {
      case token::token_kind::int_kw:
        name = "int";
        break;
      case token::token_kind::void_kw:
        name = "void";
        break;
      case token::token_kind::return_kw:
        name = "return";
        break;
      case token::token_kind::identifier:
        name = "identifier";
        break;
      case token::token_kind::number:
        name = "number";
        break;
      case token::token_kind::paren_open:
        name = "(";
        break;
      case token::token_kind::paren_close:
        name = ")";
        break;
      case token::token_kind::brace_open:
        name = "{";
        break;
      case token::token_kind::brace_close:
        name = "}";
        break;
      case token::token_kind::semicolon:
        name = ";";
        break;
      case token::token_kind::hyphen:
        name = "-";
        break;
      case token::token_kind::tilde:
        name = "~";
        break;
    }
    return std::format_to(ctx.out(), "{}", name);
  }
};

template <>
struct std::formatter<token>
{
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const token &t, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "Token({}, lexeme: \"{}\")", t.kind(), t.lexeme());
  }
};
#endif  // C_COMPILER_TOKEN_HPP
