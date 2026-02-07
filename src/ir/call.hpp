#ifndef C_COMPILER_CALL_HPP
#define C_COMPILER_CALL_HPP
#include <optional>

namespace ir
{
  struct call
  {
    explicit call(std::string name, std::optional<std::string> dst = std::nullopt) : name(std::move(name)), dst(std::move(dst)) {}

    std::string name;
    std::optional<std::string> dst;
  };
}  // namespace ir

#endif  // C_COMPILER_CALL_HPP
