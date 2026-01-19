#ifndef C_COMPILER_INSTRUCTION_HPP
#define C_COMPILER_INSTRUCTION_HPP

#include <asm/binary.hpp>
#include <asm/cdq.hpp>
#include <asm/cmp.hpp>
#include <asm/jmp.hpp>
#include <asm/label.hpp>
#include <asm/mov.hpp>
#include <asm/pop.hpp>
#include <asm/ret.hpp>
#include <asm/set.hpp>
#include <asm/start_function.hpp>
#include <asm/unary.hpp>
#include <variant>
#include <vector>

namespace x86
{
  using instruction_t = std::variant<start_function, mov, ret, unary, binary, pop, cdq, jmp, cmp, set, label>;

  // mov
  std::vector<instruction_t> legalize(const mov& m);
  // cmp
  std::vector<instruction_t> legalize(const cmp& c);
  // binary
  std::vector<instruction_t> legalize(const binary& c);


}  // namespace x86
#endif
