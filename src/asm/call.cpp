#include <asm/call.hpp>
#include <format>

std::string x86::call::emit() const {
  return std::format("  call {}", name);
}
