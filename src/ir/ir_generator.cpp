#include "ir_generator.hpp"

#include <ir/program.hpp>
#include <memory>

#include "ast/ast.hpp"
#include "ast/ast_printer.hpp"
#include "binary.hpp"
#include "call.hpp"
#include "copy.hpp"
#include "symbol.hpp"
#include "unary.hpp"

template <class... Ts>
struct overload : Ts...
{
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

ir::program ir_generator::generate(const ast::program& root) {
  ir::program prog;
  for (const auto& func : root.functions) {
    ir_generator ir_generator;
    ir_generator.emit_func(func);

    prog.functions.emplace_back(func.name, ir_generator.m_instructions);
  }

  return prog;
}

ir::value ir_generator::emit_expression(const ast::expr& expr, std::optional<std::string> target) {
  return std::visit(overload{[&](int val) -> ir::value { return ir::value{val}; },

                             [&](const Box<ast::variable>& v) -> ir::value { return ir::value{v->identifier}; },

                             [&](const Box<ast::unary>& u) -> ir::value
                             {
                               const ir::value src = emit_expression(u->child);
                               std::string dst = new_variable();

                               m_instructions.emplace_back(ir::unary{u->operation, src, dst});
                               return ir::value{dst};
                             },

                             [&](const Box<ast::binary>& b) -> ir::value
                             {
                               const ir::value lhs = emit_expression(b->left);
                               const ir::value rhs = emit_expression(b->right);
                               std::string dst = new_variable();

                               m_instructions.emplace_back(ir::binary{b->operation, lhs, rhs, dst});
                               return ir::value{dst};
                             },

                             [&](const Box<ast::assignment>& a) -> ir::value
                             {
                               const ir::value rhs = emit_expression(a->rhs);
                               const ir::value lhs = emit_expression(a->lhs);

                               m_instructions.emplace_back(ir::copy{rhs, lhs.as_id()});
                               return rhs;
                             },

                             [&](const Box<ast::call>& c) -> ir::value
                             {
                               std::string tmp = new_variable();
                               m_instructions.emplace_back(ir::symbol{tmp});
                               m_instructions.emplace_back(ir::call{c->identifier, tmp});
                               if (target.has_value()) {
                                 m_instructions.emplace_back(ir::copy{tmp, *target});
                               }
                               return {tmp};
                             }},
                    expr);
}

void ir_generator::emit_func(const ast::function& func) {
  m_instructions.emplace_back(ir::function(func.name));
  emit_block(func.body);
}

void ir_generator::emit_block(const ast::block& block) {
  m_instructions.emplace_back(ir::begin_scope{});
  for (const auto& item : block.items) {
    emit_block_item(item);
  }
  m_instructions.emplace_back(ir::end_scope{});
}

void ir_generator::emit_statement(const ast::statement& stmt) {
  std::visit(overloaded{[&](const Box<ast::return_stmt>& s)
                        {
                          const ir::value val = emit_expression(s->value);
                          m_instructions.emplace_back(ir::return_{val});
                        },

                        [&](const Box<ast::if_stmt>& s)
                        {
                          const std::string end_label = new_label();

                          const ir::value cond = emit_expression(s->condition);
                          m_instructions.emplace_back(ir::jump_if_zero{cond, end_label});

                          emit_statement(s->then_branch);
                          m_instructions.emplace_back(ir::label{end_label});
                        },
                        [&](const Box<ast::while_stmt>& w)
                        {
                          const std::string start_label = new_label();
                          const std::string end_label = new_label();
                          m_instructions.emplace_back(ir::label(start_label));
                          const ir::value cond = emit_expression(w->condition);
                          m_instructions.emplace_back(ir::jump_if_zero(cond, end_label));
                          emit_statement(w->body);
                          m_instructions.emplace_back(ir::jump(start_label));
                          m_instructions.emplace_back(ir::label(end_label));
                        },
                        [&](const Box<ast::block>& b)
                        {
                          m_instructions.emplace_back(ir::begin_scope{});
                          for (const auto& item : b->items) {
                            emit_block_item(item);
                          }
                          m_instructions.emplace_back(ir::end_scope{});
                        },

                        [&](const Box<ast::for_stmt>& f)
                        {
                          const auto start_label = new_label();
                          const auto end_label = new_label();
                          emit_declaration(f->init);
                          m_instructions.emplace_back(ir::label(start_label));
                          const auto cond = emit_expression(f->condition);
                          m_instructions.emplace_back(ir::jump_if_zero(cond, end_label));
                          emit_statement(f->body);
                          emit_expression(f->post);
                          m_instructions.emplace_back(ir::jump(start_label));
                          m_instructions.emplace_back(ir::label(end_label));
                        },

                        [&](const ast::expr& e) { emit_expression(e); },

                        [&](const std::monostate&) {}},
             stmt);
}

void ir_generator::emit_declaration(const ast::declaration& decl) {
  m_instructions.emplace_back(ir::symbol(decl.identifier));
  if (decl.init) {
    const ir::value initial_val = emit_expression(decl.init.value(), decl.identifier);
    if (std::holds_alternative<Box<ast::call>>(decl.init.value())) {
    }
    else {
      m_instructions.emplace_back(ir::copy{initial_val, decl.identifier});
    }
  }
}

void ir_generator::emit_block_item(const ast::block_item& item) {
  std::visit(overload{[&](const std::unique_ptr<ast::statement>& stmt) { emit_statement(*stmt); },
                      [&](const std::unique_ptr<ast::declaration>& decl) { emit_declaration(*decl); }},
             item);
}

std::string ir_generator::new_variable() { return "t." + std::to_string(tmp_variable_suffix++); }
std::string ir_generator::new_label() { return "L." + std::to_string(tmp_label_suffix++); }
