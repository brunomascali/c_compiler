#ifndef C_COMPILER_AST_PRINTER_HPP
#define C_COMPILER_AST_PRINTER_HPP

#include <string>

#include <ast/ast_fwd.hpp>
#include <ast/program.hpp>
#include <ast/function.hpp>
#include <ast/expr/assignment.hpp>
#include <ast/expr/binary.hpp>
#include <ast/expr/unary.hpp>
#include <ast/expr/call.hpp>
#include <ast/expr/variable.hpp>

#include <ast/statement/block_item.hpp>
#include <ast/statement/block.hpp>
#include <ast/statement/declaration.hpp>
#include <ast/statement/for.hpp>
#include <ast/statement/if.hpp>
#include <ast/statement/return.hpp>
#include <ast/statement/while.hpp>

template <class... Ts>
struct overloaded : Ts...
{
  using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void print_node(const ast::program& p);
void print_node(const ast::function& f, const std::string& prefix, bool is_last);
void print_node(const ast::block& b, const std::string& prefix, bool is_last);
void print_node(const ast::declaration& d, const std::string& prefix, bool is_last);
void print_node(const ast::statement& s, const std::string&, bool is_last);
void print_node(const ast::return_& r, const std::string& prefix, bool is_last);
void print_node(const ast::while_& r, const std::string& prefix, bool is_last);
void print_node(const ast::for_& f, const std::string& prefix, bool is_last);
void print_node(const ast::block_item& r, const std::string& prefix, bool is_last);
void print_node(const ast::expr& e, const std::string& prefix, bool is_last);
void print_node(const ast::if_& i, const std::string& prefix, bool is_last);
inline void print_node(const std::monostate&, const std::string&, bool) {}

[[nodiscard]] std::string op_to_string(const ast::binary::op& op);

#endif
