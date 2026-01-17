#ifndef C_COMPILER_BIT_WIDTH_HPP
#define C_COMPILER_BIT_WIDTH_HPP

#include <string>

namespace x86 {
enum class bit_width { byte, word, dword, qword };

[[nodiscard]] inline std::string to_string(const bit_width b) {
  switch (b) {
  case bit_width::byte: return "b";
  case bit_width::word: return "w";
  case bit_width::dword: return "l";
  case bit_width::qword: return "q";
  }
  throw std::invalid_argument("unreachable");
}
} // namespace x86

#endif // C_COMPILER_BIT_WIDTH_HPP
