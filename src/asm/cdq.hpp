#ifndef C_COMPILER_CDQ_HPP
#define C_COMPILER_CDQ_HPP

namespace x86
{
  struct cdq
  {
  };

  [[nodiscard]] inline std::string to_string(const cdq&) { return "  cltd"; }
}  // namespace x86

#endif  // C_COMPILER_CDQ_HPP
