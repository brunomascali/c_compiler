#include <asm/cdq.hpp>

namespace x86
{
  std::string cdq::emit() const {
    return "cltd";
  }
}
