#ifndef C_COMPILER_TOKEN_HPP
#define C_COMPILER_TOKEN_HPP

#include <format>
#include <string>

class token {
 public:
  enum class token_kind
  {
    // Keywords
    int_kw,
    void_kw,
    return_kw,
    if_kw,
    else_kw,
    while_kw,
    for_kw,
    // non-fixed tokens
    identifier,
    number,
    // punctuation
    paren_open,
    paren_close,
    brace_open,
    brace_close,
    semicolon,
    equal,
    hyphen,
    tilde,
    plus,
    asterisk,
    slash,
    percent,

    // operators
    negation,
    double_ampersand,
    double_pipe,
    double_eq,
    neq,
    lt,
    gt,
    le,
    ge,
    post_inc,
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
    case tk::plus:
    case tk::hyphen:
      return 45;
    case tk::lt:
    case tk::gt:
    case tk::le:
    case tk::ge:
      return 35;
    case tk::neq:
    case tk::double_eq:
      return 30;
    case tk::double_ampersand:
      return 10;
    case tk::double_pipe:
      return 5;
    case tk::equal:
      return 1;
    default:
      return std::nullopt;
  }
}

constexpr std::string_view to_string(const token::token_kind k) {
  using enum token::token_kind;
  switch (k) {
    case int_kw:
      return "int";
    case void_kw:
      return "void";
    case return_kw:
      return "return";
    case identifier:
      return "identifier";
    case number:
      return "number";
    case paren_open:
      return "(";
    case paren_close:
      return ")";
    case brace_open:
      return "{";
    case brace_close:
      return "}";
    case semicolon:
      return ";";
    case hyphen:
      return "-";
    case tilde:
      return "~";
    case plus:
      return "+";
    case asterisk:
      return "*";
    case slash:
      return "/";
    case percent:
      return "%";
    case negation:
      return "!";
    case double_ampersand:
      return "&&";
    case double_pipe:
      return "||";
    case double_eq:
      return "==";
    case neq:
      return "!=";
    case lt:
      return "<";
    case gt:
      return ">";
    case le:
      return "<=";
    case ge:
      return ">=";
    case if_kw:
      return "if";
    case else_kw:
      return "else";
    case equal:
      return "==";
    case post_inc:
      return "++";
    default:
      return "unknown_token";
  }
}


template <>
struct std::formatter<token::token_kind>
{
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(token::token_kind k, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "{}", to_string(k));
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
