#ifndef C_COMPILER_START_FUNCTION_HPP
#define C_COMPILER_START_ FUNCTION_HPP

#include <memory>
#include <string>

namespace x86
{
  struct start_function
  {
    std::string name;

    explicit start_function(std::string n) : name(std::move(n)) {}
  };
}  // namespace x86

#endif
