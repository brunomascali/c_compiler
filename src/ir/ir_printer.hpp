#ifndef C_COMPILER_IR_PRINTER_HPP
#define C_COMPILER_IR_PRINTER_HPP

#include <ir/defs.hpp>
#include <ir/program.hpp>

namespace ir
{
  void print(const program& p);
  void print(const function& f);
  void print(const instruction& ins);
}  // namespace ir

#endif  // C_COMPILER_IR_PRINTER_HPP
