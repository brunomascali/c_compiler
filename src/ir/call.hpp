#ifndef C_COMPILER_IR_CALL_HPP
#define C_COMPILER_IR_CALL_HPP

#include <string>
#include <optional>

namespace ir
{
  struct call
  {
    explicit call(std::string name, std::optional<std::string> dst = std::nullopt) : function_name(std::move(name)), dst(std::move(dst)) {}

    std::string function_name;
    std::optional<std::string> dst;
  };
}  // namespace ir

#endif  // C_COMPILER_IR_CALL_HPP
