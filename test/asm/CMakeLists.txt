add_executable(asm_tests test_asm.cpp)

target_link_libraries(asm_tests
        PRIVATE
        asm_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(asm_tests)
