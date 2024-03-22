#pragma once

#include "Token.hpp"

#include <optional>
#include <iostream>
#include <vector>

namespace altercc
{

class Lexer
{
public:
    Lexer(std::istream &input, bool const token_verbose = false)
        : input_{input}
        , location_{}
        , token_verbose_{token_verbose}
    {
    }

    Token get();
    Token peek();
    std::vector<Token> collect();
    bool eof() const;

    Location get_location() const
    {
        return this->location_;
    }

    static void dump_tokens(std::ostream &os, std::vector<Token> const& tokens);

protected:
    char peek_char() const;
    char get_char();
    void skip_spaces();
    Token get_next();
    Token get_string_token();
    Token get_numeric_token();

    std::istream        &input_;
    Location             location_;
    std::optional<Token> next_token_;

    bool const           token_verbose_;
};

} // namespace altercc