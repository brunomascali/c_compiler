#include <print>
#include <ast/ast_printer.hpp>

std::string branch(bool is_last) {
    return is_last ? "╰─ " : "╞─ ";
}

void print_node(const ast::program& p) {
    std::cout << "main" << std::endl;
    for (size_t i = 0; i < p.functions.size(); ++i) {
        bool last = (i == p.functions.size() - 1);
        print_node(p.functions[i], "", last);
    }
}

void print_node(const ast::function& f, std::string prefix, bool is_last) {
    for (size_t i = 0; i < f.body.size(); ++i) {
        bool last = (i == f.body.size() - 1);
        print_node(f.body[i], prefix, last);
    }
}

void print_node(const ast::block_item& b, std::string prefix, bool is_last) {
    std::visit([&](auto&& arg) { print_node(arg, prefix, is_last); }, b);
}

void print_node(const ast::statement& s, std::string prefix, bool is_last) {
  std::visit([&](auto&& arg) {
    print_node(arg, prefix, is_last);
  }, s);
}

void print_node(const ast::declaration& d, std::string prefix, bool is_last) {
    std::println("{}{}Declaration", prefix, branch(is_last));

    const auto child_prefix = prefix + (is_last ? "   " : "│  ");

    std::println("{}╞─ Variable {}", child_prefix, d.identifier);

    std::cout << child_prefix << "╰─ Expression" << std::endl;
    if (d.expression) {
        print_node(d.expression.value(), child_prefix + "   ", true);
    }
}

void print_node(const ast::return_stmt& r, std::string prefix, bool is_last) {
    std::cout << prefix << branch(is_last) << "Return" << std::endl;
    std::string child_prefix = prefix + (is_last ? "   " : "│  ");

    std::cout << child_prefix << "╰─ Expression" << std::endl;
    print_node(r.expression, child_prefix + "   ", true);
}

void print_node(const ast::expr& e, std::string prefix, bool is_last) {
    std::visit(overloaded{
        [&](int n) {
            std::cout << prefix << branch(is_last) << "Number " << n << std::endl;
        },
        [&](const std::unique_ptr<ast::binary>& bin) {
            std::cout << prefix << branch(is_last) << "Binary Op" << std::endl;
            std::string child_prefix = prefix + (is_last ? "   " : "│  ");
            print_node(bin->left, child_prefix, false);
            print_node(bin->right, child_prefix, true);
        },
        [&](const std::unique_ptr<ast::variable>& var) {
            std::cout << prefix << branch(is_last) << "Variable: " << var->identifier << std::endl;
        },
        [&](const auto&) {
            std::cout << prefix << branch(is_last) << "Other Expression" << std::endl;
        }
    }, e);
}