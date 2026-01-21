#ifndef C_COMPILER_CODEGEN_CONTEXT_HPP
#define C_COMPILER_CODEGEN_CONTEXT_HPP

#include <format>
#include <map>
#include <string>

namespace x86
{
  class codegen_context {
   public:
    int32_t get_variable_stack_offset(const std::string& ir_var) {
      if (not m_locals.contains(ir_var.data())) {
        throw std::logic_error("Cannot find local variable " + ir_var);
      }

      return m_locals[ir_var.data()];
    }

    int32_t create_stack_offset(std::string ir_var) {
      if (m_locals.contains(ir_var.data())) {
        throw std::logic_error("Variable " + ir_var + " Already declared.");
      }
      m_current_offset -= 4;
      m_locals[ir_var.data()] = m_current_offset;

      return m_locals[std::move(ir_var)];
    }

    bool has_declared_variable(const std::string& ir_var) const {
      return m_locals.contains(ir_var);
    }

    std::string create_label() { return std::format(".L{}", m_current_label); }

    [[nodiscard]] int32_t total_stack_usage() const;

   private:
    std::map<std::string, int32_t> m_locals;
    int32_t m_current_offset{0};
    int32_t m_current_label{0};
  };
}  // namespace x86

#endif  // C_COMPILER_CODEGEN_CONTEXT_HPP
