#include <asm/leave.hpp>

std::string x86::leave::emit() const {
  return "  leave";
}
