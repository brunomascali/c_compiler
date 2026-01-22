#ifndef C_COMPILER_VALUE_HPP
#define C_COMPILER_VALUE_HPP

#include <string>
#include <variant>

namespace ir
{
  using immediate = int;
  using identifier = std::string;

  struct value : std::variant<immediate, identifier>
  {
    using variant::variant;

    [[nodiscard]] bool is_immediate() const { return std::holds_alternative<immediate>(*this); }
    [[nodiscard]] bool is_identifier() const { return std::holds_alternative<identifier>(*this); }

    [[nodiscard]] const identifier& as_id() const { return std::get<identifier>(*this); }
    [[nodiscard]] immediate as_imm() const { return std::get<immediate>(*this); }
  };
}  // namespace ir

#endif  // C_COMPILER_VALUE_HPP
