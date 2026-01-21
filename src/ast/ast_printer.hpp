#ifndef C_COMPILER_AST_PRINTER_HPP
#define C_COMPILER_AST_PRINTER_HPP

#include <ast/ast.hpp>
#include <iostream>
#include <string>
#include <variant>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void print_node(const ast::program& p);

void print_node(const ast::function& f, std::string prefix, bool is_last);
void print_node(const ast::block_item& b, std::string prefix, bool is_last);
void print_node(const ast::declaration& d, std::string prefix, bool is_last);
void print_node(const ast::statement& s, std::string prefix, bool is_last);
void print_node(const ast::return_stmt& r, std::string prefix, bool is_last);
void print_node(const ast::expr& e, std::string prefix, bool is_last);
inline void print_node(const std::monostate&, std::string, bool) {}

#endif