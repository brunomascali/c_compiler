#ifndef C_COMPILER_IR_HPP
#define C_COMPILER_IR_HPP

#include <ast/ast.hpp>
#include <ast/ast_fwd.hpp>
#include <ir/defs.hpp>
#include <ir/program.hpp>
#include <memory>
#include <vector>

namespace ir
{
  template <typename T>
  using Box = std::unique_ptr<T>;

  class generator {
   public:
    static program generate(const ast::program &root);

   private:
    void emit_func(const ast::function &func);
    void emit_block(const ast::block& block);
    void emit_block_item(const ast::block_item &item);
    void emit_statement(const ast::statement &stmt);
    void emit_declaration(const ast::declaration &decl);
    value emit_expression(const ast::expr &expr);

    std::string new_variable();
    std::string new_label();

    std::vector<instruction> m_instructions{};
    int tmp_variable_suffix{0};
    int tmp_label_suffix{0};
  };  // namespace ir
}  // namespace ir

#endif  // C_COMPILER_IR_HPP
