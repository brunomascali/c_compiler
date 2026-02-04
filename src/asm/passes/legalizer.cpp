#include "legalizer.hpp"

#include "asm/mov.hpp"

namespace x86
{

  std::vector<instruction> legalizer::run(instruction& input) {
    {
      if (input.is_legal()) {
        return { input };
      }
      return input.legalize();
    }
  }
}  // namespace x86
