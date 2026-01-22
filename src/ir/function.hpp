#ifndef C_COMPILER_FUNCTION_HPP
#define C_COMPILER_FUNCTION_HPP

namespace ir {
  struct instruction;

  struct function {
    std::string name;
    std::vector<instruction> instructions;

    size_t temp_count;
  };
} // namespace ir

#endif // C_COMPILER_FUNCTION_HPP
