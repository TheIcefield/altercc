set(target_name lexer_tests)

add_executable(
    ${target_name}
    lexer_test.cpp
)

target_link_libraries(${target_name} PRIVATE
    altercc-lib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${target_name})
