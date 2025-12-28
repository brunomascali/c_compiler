#ifndef C_COMPILER_ASMEMITTER_HPP
#define C_COMPILER_ASMEMITTER_HPP

#include <vector>

#include "ret.hpp"
#include "start_function.hpp"
#include "mov.hpp"
#include "ast/ast.hpp"

class asm_emitter {
public:
  using instruction = std::variant<x86::start_function, x86::mov, x86::ret>;

  std::vector<instruction> emit(const ast::program &program);

private:
  std::vector<instruction> m_instructions;


  void visit_statement(const ast::statement &statement);

  void asm_from_return_ast_node(const ast::return_stmt &statement);

  void gen_from_function_ast_node(const ast::function &function);
};


#endif //C_COMPILER_ASMEMITTER_HPP
