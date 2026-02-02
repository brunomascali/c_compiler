#ifndef C_COMPILER_CDQ_HPP
#define C_COMPILER_CDQ_HPP
#include <string>

namespace x86
{
  struct cdq
  {
    [[nodiscard]] std::string emit() const;
  };
}  // namespace x86

#endif  // C_COMPILER_CDQ_HPP
