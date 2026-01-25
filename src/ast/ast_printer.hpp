#ifndef C_COMPILER_AST_PRINTER_HPP
#define C_COMPILER_AST_PRINTER_HPP

#include <ast/ast.hpp>
#include <string>

#include "expr.hpp"

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void print_node(const ast::program& p);
void print_node(const ast::function& f, const std::string& prefix, bool is_last);
void print_node(const ast::block& b, const std::string& prefix, bool is_last);
void print_node(const ast::declaration& d, const std::string& prefix, bool is_last);
void print_node(const ast::statement& s, const std::string&, bool is_last);
void print_node(const ast::return_stmt& r, const std::string& prefix, bool is_last);
void print_node(const ast::block_item& r, const std::string& prefix, bool is_last);
void print_node(const ast::expr& e, const std::string& prefix, bool is_last);
void print_node(const ast::if_stmt& i, const std::string& prefix, bool is_last);
inline void print_node(const std::monostate&, const std::string&, bool) {}

[[nodiscard]] std::string op_to_string(const ast::binary::op& op);

#endif