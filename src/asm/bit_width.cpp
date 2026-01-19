#include <asm/bit_width.hpp>
#include <stdexcept>

namespace x86
{
  std::string to_string(const bit_width b) {
    {
      switch (b) {
        case bit_width::byte:
          return "b";
        case bit_width::word:
          return "w";
        case bit_width::dword:
          return "l";
        case bit_width::qword:
          return "q";
      }
      throw std::invalid_argument("unreachable");
    }
  }
}