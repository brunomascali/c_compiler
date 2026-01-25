#include <ast/ast_printer.hpp>
#include <iostream>
#include <print>

std::string branch(const bool is_last) { return is_last ? "╰─ " : "╞─ "; }

void print_node(const ast::program& p) {
  std::cout << "main" << std::endl;
  for (size_t i = 0; i < p.functions.size(); ++i) {
    const bool last = (i == p.functions.size() - 1);
    print_node(p.functions[i], "", last);
  }
}

void print_node(const ast::function& f, const std::string& prefix, bool is_last) {
  for (size_t i = 0; i < f.body.items.size(); ++i) {
    const bool last = (i == f.body.items.size() - 1);
    print_node(f.body.items[i], prefix, last);
  }
}

void print_node(const ast::block& b, const std::string& prefix, bool is_last) {
  for (size_t i = 0; i < b.items.size(); ++i) {
    const bool last = (i == b.items.size() - 1);
    print_node(b.items[i], prefix, last);
  }
}

void print_node(const ast::statement& s, const std::string& prefix, bool is_last) {
  std::visit(overloaded{[&](const std::monostate&) {}, [&](const ast::expr& e) { print_node(e, prefix, is_last); },
                        [&](auto&& arg)
                        {
                          if (arg) {
                            print_node(*arg, prefix, is_last);
                          }
                        }},
             s);
}

void print_node(const ast::declaration& d, const std::string& prefix, bool is_last) {
  std::println("{}{}Declaration", prefix, branch(is_last));

  const auto child_prefix = prefix + (is_last ? "   " : "│  ");

  std::println("{}╞─ Variable {}", child_prefix, d.identifier);

  std::cout << child_prefix << "╰─ Expression" << std::endl;
  if (d.init) {
    print_node(d.init.value(), child_prefix + "   ", true);
  }
}

void print_node(const ast::return_stmt& r, const std::string& prefix, const bool is_last) {
  std::cout << prefix << branch(is_last) << "Return" << std::endl;
  const std::string child_prefix = prefix + (is_last ? "   " : "│  ");

  std::cout << child_prefix << "╰─ Expression" << std::endl;
  print_node(r.value, child_prefix + "   ", true);
}

void print_node(const ast::block_item& r, const std::string& prefix, bool is_last) {
  std::visit(overloaded{
      [&](const std::monostate&) {
      },
      [&](const auto& arg) {
          if (arg) {
              print_node(*arg, prefix, is_last);
          }
      }
  }, r);
}
void print_node(const ast::expr& e, const std::string& prefix, bool is_last) {
  std::visit(
    overloaded{[&](const int n) { std::cout << prefix << branch(is_last) << "Number " << n << std::endl; },
               [&](const std::unique_ptr<ast::binary>& bin)
               {
                 std::cout << prefix << branch(is_last) << op_to_string(bin->operation) << std::endl;
                 const std::string child_prefix = prefix + (is_last ? "   " : "│  ");
                 print_node(bin->left, child_prefix, false);
                 print_node(bin->right, child_prefix, true);
               },
               [&](const std::unique_ptr<ast::variable>& var)
               { std::cout << prefix << branch(is_last) << "Variable: " << var->identifier << std::endl; },
               [&](const auto&) { std::cout << prefix << branch(is_last) << "Other Expression" << std::endl; }},
    e);
}

void print_node(const ast::if_stmt& i, const std::string& prefix, bool is_last) {
  std::println("{}{}If Statement", prefix, branch(is_last));
  const auto child_prefix = prefix + (is_last ? "   " : "│  ");

  std::println("{}╞─ Condition", child_prefix);
  print_node(i.condition, child_prefix + "│  ", false);

  std::println("{}╞─ Then", child_prefix);
  print_node(i.then_branch, child_prefix + "│  ", !(i.else_branch.has_value()));

  if (i.else_branch) {
    std::println("{}╰─ Else", child_prefix);
    print_node(i.else_branch.value(), child_prefix + "   ", true);
  }
}

std::string op_to_string(const ast::binary::op& op) {
  switch (op) {
    case ast::binary::op::add:
      return "add";
    case ast::binary::op::sub:
      return "sub";
    case ast::binary::op::mul:
      return "mul";
    case ast::binary::op::div:
      return "div";
    case ast::binary::op::rem:
      return "rem";
    case ast::binary::op::and_:
      return "and";
    case ast::binary::op::or_:
      return "or";
    case ast::binary::op::eq:
      return "eq";
    case ast::binary::op::neq:
      return "neq";
    case ast::binary::op::lt:
      return "lt";
    case ast::binary::op::gt:
      return "gt";
    case ast::binary::op::le:
      return "le";
    case ast::binary::op::ge:
      return "ge";
    case ast::binary::op::assign:
      return "mov";
    default:
      return "unknown";
  }
}
