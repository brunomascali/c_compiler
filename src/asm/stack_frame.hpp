#ifndef C_COMPILER_CODEGEN_CONTEXT_HPP
#define C_COMPILER_CODEGEN_CONTEXT_HPP

#include <algorithm>
#include <format>
#include <map>
#include <ranges>
#include <string>
#include <vector>

namespace x86
{
  class stack_frame {
   public:
    [[nodiscard]] int32_t get_variable_stack_offset(const std::string& variable_name) const {
      for (const auto& declared_variables : std::views::reverse(m_locals)) {
        if (const auto x = declared_variables.find(variable_name); x != declared_variables.end()) return x->second;
      }

      throw std::logic_error("Cannot find variable " + variable_name);
    }

    int32_t resolve_variable_offset(const std::string& variable_name) {
      for (const auto& declared_variables : std::views::reverse(m_locals)) {
        if (const auto x = declared_variables.find(variable_name); x != declared_variables.end()) return x->second;
      }

      return create_stack_offset(variable_name);
    }

    int32_t create_stack_offset(const std::string& variable_name) {
      if (m_symbols.back().contains(variable_name)) {
        throw std::logic_error("Variable " + variable_name + " Already declared.");
      }
      m_current_offset -= 4;
      m_locals.back()[variable_name] = m_current_offset;
      return m_current_offset;
    }

    [[nodiscard]] bool has_declared_variable(const std::string& ir_var) const {
      const auto rev = std::views::reverse(m_locals);
      return std::ranges::any_of(rev, [ir_var](const auto& var) { return var.contains(ir_var); });
    }

    [[nodiscard]] bool has_declared_symbol(const std::string& ir_var) const {
      return std::ranges::any_of(m_symbols, [ir_var](const auto& var) { return var.contains(ir_var); });
    }

    void register_symbol(const std::string& name) {
      if (m_symbols.back().contains(name)) {
        throw std::logic_error(std::format("ERROR: {} already declared in this scope", name));
      }
      const int32_t offset = allocate_new_slot(name);
      m_symbols.back()[name] = offset;
    }

    void push_scope() {
      m_locals.emplace_back();
      m_symbols.emplace_back();
    }

    void pop_scope() {
      m_locals.pop_back();
      m_symbols.pop_back();
    }

    std::string create_label() { return std::format(".L{}", m_current_label); }

    [[nodiscard]] int32_t total_stack_usage() const;

   private:
    std::vector<std::map<std::string, int32_t>> m_locals;
    std::vector<std::map<std::string, int32_t>> m_symbols;
    int32_t m_current_offset{0};
    int32_t m_current_label{0};

    int32_t allocate_new_slot(const std::string& name) {
      m_current_offset -= 4;
      m_locals.back()[name] = m_current_offset;
      return m_current_offset;
    }
  };
}  // namespace x86

#endif  // C_COMPILER_CODEGEN_CONTEXT_HPP
