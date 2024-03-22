set(target_name altercc-lib)

add_library(${target_name} STATIC
    altercc/error_listener/ErrorListener.hpp
    altercc/error_listener/ErrorListener.cpp

    altercc/lexer/Token.hpp
    altercc/lexer/Token.cpp
    altercc/lexer/Lexer.hpp
    altercc/lexer/Lexer.cpp
)

target_include_directories(${target_name} PUBLIC .)
