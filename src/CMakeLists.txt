add_subdirectory(utils)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(ast)
add_subdirectory(asm)
add_subdirectory(ir)

set(ALL_LIBS lexer_lib parser_lib ast_lib utils_lib asm_lib ir_lib)

foreach(lib ${ALL_LIBS})
    target_include_directories(${lib} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
endforeach()

add_executable(c_compiler main.cpp
)
target_link_libraries(c_compiler PRIVATE
        utils_lib
        lexer_lib
        ast_lib
        parser_lib
        asm_lib
        ir_lib
)