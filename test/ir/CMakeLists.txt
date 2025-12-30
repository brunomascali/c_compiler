add_executable(ir_tests test_ir.cpp)

target_link_libraries(ir_tests
        PRIVATE
        asm_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ir_tests)
