#ifndef C_COMPILER_BIT_WIDTH_HPP
#define C_COMPILER_BIT_WIDTH_HPP

#include <string>

namespace x86
{
  enum class bit_width
  {
    byte,
    word,
    dword,
    qword
  };

  [[nodiscard]] std::string to_string(bit_width b);
}  // namespace x86

#endif  // C_COMPILER_BIT_WIDTH_HPP
