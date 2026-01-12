#ifndef C_COMPILER_FUNCTION_HPP
#define C_COMPILER_FUNCTION_HPP

namespace ir {
struct start_function {
  explicit start_function(const ast::function &func) : name(func.name) {}

  std::string name;
};
} // namespace ir

#endif // C_COMPILER_FUNCTION_HPP
