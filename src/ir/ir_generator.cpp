#include "ir_generator.hpp"

#include <ir/program.hpp>
#include <memory>

#include "ast/ast.hpp"
#include "binary.hpp"
#include "copy.hpp"
#include "unary.hpp"


template <class... Ts>
struct overload : Ts...
{
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

namespace ir
{
  program generator::generate(const ast::program& root) {
    program prog;
    for (const auto& func : root.functions) {
      generator generator;
      generator.emit_func(func);

      prog.functions.emplace_back(func.name, generator.m_instructions);
    }

    return prog;
  }

  value generator::emit_expression(const ast::expr& expr) {
    return std::visit(overload{[&](int val) -> value { return value{val}; },

                               [&](const Box<ast::variable>& v) -> value { return value{v->identifier}; },

                               [&](const Box<ast::unary>& u) -> value
                               {
                                 const value src = emit_expression(u->child);
                                 std::string dst = new_variable();  // Generate a temporary name like "t1"

                                 m_instructions.emplace_back(ir::unary{u->operation, src, dst});
                                 return value{dst};
                               },

                               [&](const Box<ast::binary>& b) -> value
                               {
                                 const value lhs = emit_expression(b->left);
                                 const value rhs = emit_expression(b->right);
                                 std::string dst = new_variable();

                                 m_instructions.emplace_back(ir::binary{b->operation, lhs, rhs, dst});
                                 return value{dst};
                               },

                               [&](const Box<ast::assignment>& a) -> ir::value
                               {
                                 const value rhs = emit_expression(a->rhs);
                                 const value lhs = emit_expression(a->lhs);

                                 m_instructions.emplace_back(ir::copy{rhs, lhs.as_id()});
                                 return rhs;
                               }},
                      expr);
  }
  void generator::emit_func(const ast::function& func) {
    for (const auto& stmt : func.body.items) {
      emit_statement(stmt);
    }
  }

  void generator::emit_statement(const ast::statement& stmt) {
    std::visit(overload{[&](const Box<ast::return_stmt>& s)
                        {
                          const value val = emit_expression(s->value);
                          m_instructions.emplace_back(ir::return_{val});
                        },

                        [&](const Box<ast::declaration>& d)
                        {
                          if (d->init) {
                            const value initial_val = emit_expression(d->init.value());
                            m_instructions.emplace_back(ir::copy{initial_val, d->identifier});
                          }
                        },

                        [&](const Box<ast::if_stmt>& s)
                        {
                          const std::string else_label = new_label();
                          const std::string end_label = new_label();

                          const value cond = emit_expression(s->condition);

                          m_instructions.emplace_back(ir::jump_if_zero{cond, else_label});

                          emit_statement(s->then_branch);
                          m_instructions.emplace_back(ir::jump{end_label});

                          m_instructions.emplace_back(ir::label{else_label});
                          if (s->else_branch) {
                            emit_statement(s->else_branch.value());
                          }

                          m_instructions.emplace_back(ir::label{end_label});
                        },

                        [&](const Box<ast::block>& b)
                        {
                          for (const auto& item : b->items) {
                            emit_statement(item);
                          }
                        },

                        [&](const ast::expr& e) { emit_expression(e); },

                        [&](const std::monostate&) {}},
               stmt);
  }

  std::string generator::new_variable() { return "t." + std::to_string(tmp_variable_suffix++); }
  std::string generator::new_label() { return "L." + std::to_string(tmp_label_suffix++); }
}  // namespace ir
