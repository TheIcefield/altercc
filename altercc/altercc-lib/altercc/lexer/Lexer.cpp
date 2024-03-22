#include "Lexer.hpp"

#include <iostream>
#include <cassert>

namespace altercc
{

static bool g_is_eof = false;

Token Lexer::get()
{
    auto const token = this->get_next();

    if (this->token_verbose_)
    {
        std::cout << token << "\n";
    }

    return token;
}

Token Lexer::get_next()
{
    auto const location = this->get_location();

    if (this->next_token_.has_value())
    {
        Token token = this->next_token_.value();
        this->next_token_.reset();
        return token;
    }
    
    this->skip_spaces();

    if (this->eof())
    {
        assert(!g_is_eof);

        g_is_eof = true;
        return Token (Token::Kind::Eof, location);
    }

    auto const next_char = this->peek_char();

    switch (next_char)
    {
        case '+':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::AddAssign, location);
            }

            return Token(Token::Kind::Plus, location);
        }

        case '-':
        {
            this->get_char();

            if (this->peek_char() == '>')
            {
                this->get_char();
                return Token(Token::Kind::Arrow, location);
            }
            
            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::SubAssign, location);
            }

            return Token(Token::Kind::Comma, location);
        }

        case '*':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::MulAssign, location);
            }

            return Token(Token::Kind::Mul, location);
        }

        case '/':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::DivAssign, location);
            }

            return Token(Token::Kind::Div, location);
        }
    
        case '%':
        {
            this->get_char();
        
            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::ModAssign, location);
            }
            
            return Token(Token::Kind::Mod, location);
        }

        case '<':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::Lte, location);
            }

            if (this->peek_char() == '<')
            {
                this->get_char();

                if (this->peek_char() == '=')
                {
                    this->get_char();
                    return Token(Token::Kind::LshiftAssign, location);
                }

                return Token(Token::Kind::Lshift, location);
            }

            return Token(Token::Kind::Lt, location);
        }

        case '>':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::Gt, location);
            }
            
            if (this->peek_char() == '>')
            {
                this->get_char();

                if (this->peek_char() == '=')
                {
                    this->get_char();
                    return Token(Token::Kind::RshiftAssign, location);
                }

                return Token(Token::Kind::Rshift, location);
            }

            return Token(Token::Kind::Gt,  location);
        }

        case '.':
        {
            this->get_char();
            return Token(Token::Kind::Dot, location);
        }

        case ',':
        {
            this->get_char();
            return Token(Token::Kind::Comma, location);
        }

        case ':':
        {
            this->get_char();
            return Token(Token::Kind::Colon, location);
        }

        case ';':
        {
            this->get_char();
            return Token(Token::Kind::Semicolon, location);
        }

        case '(':
        {
            this->get_char();
            return Token(Token::Kind::Lparen, location);
        }

        case ')':
        {
            this->get_char();
            return Token(Token::Kind::Rparen, location);
        }

        case '[':
        {
            this->get_char();
            return Token(Token::Kind::Lsb, location);
        }

        case ']':
        {
            this->get_char();
            return Token(Token::Kind::Rsb, location);
        }

        case '{':
        {
            this->get_char();
            return Token(Token::Kind::Lcb, location);
        }

        case '}':
        {
            this->get_char();
            return Token(Token::Kind::Rcb, location);
        }

        case '!':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::Neq, location);
            }

            return Token(Token::Kind::Not, location);
        }

        case '=':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::Eq, location);
            }

            return Token(Token::Kind::Assign, location);
        }

        case '&':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::AndAssign, location);
            }

            if (this->peek_char() == '&')
            {
                this->get_char();
                return Token(Token::Kind::LogicAnd, location);
            }

            return Token(Token::Kind::BitwiseAnd, location);
        }

        case '|':
        {
            this->get_char();

            if (this->peek_char() == '|')
            {
                this->get_char();
                return Token(Token::Kind::LogicOr, location);
            }

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::OrAssign, location);
            }

            return Token(Token::Kind::BitwiseOr, location);
        }

        case '^':
        {
            this->get_char();

            if (this->peek_char() == '=')
            {
                this->get_char();
                return Token(Token::Kind::XorAssign, location);
            }

            return Token(Token::Kind::BitwiseXor, location);
        }

        default:
        {
            if (isdigit(next_char))
            {
                return get_numeric_token();
            }

            if (isalpha(next_char) || next_char == '_')
            {
                return get_string_token();
            }
        }
    }

    return Token(Token::Kind::Unknown, location);
}

Token Lexer::peek()
{
    if (this->next_token_.has_value())
    {
        return this->next_token_.value();
    }

    this->next_token_ = get_next();
    return this->next_token_.value();
}

char Lexer::peek_char() const
{
    return this->input_.peek();
}

char Lexer::get_char()
{
    char current;
    this->input_.get(current);

    if (current == '\n')
    {
        this->location_.row_ += 1;
        this->location_.col_ = 1;
    }
    else
    {
        this->location_.col_++;
    }

    return current;
}

void Lexer::skip_spaces()
{
    while (isspace(this->peek_char()) != 0)
    {
        this->get_char();
    }
}

bool Lexer::eof() const
{
    return this->input_.peek() == EOF;
}

Token Lexer::get_numeric_token()
{
    auto const location = this->get_location();
    std::string text = "";
    bool is_decimal = false;

    while (  !this->eof()
          && (  std::isdigit(this->peek_char()) != 0
             || this->peek_char() == '.'))
    {
        if (this->peek_char() == '.')
        {
            is_decimal = true;
        }

        text += this->get_char();
    }

    if (is_decimal)
    {
        return Token(Token::Kind::Decimal, location, text);
    }

    return Token(Token::Kind::Integer, location, text);
}

Token Lexer::get_string_token()
{
    auto const location = this->get_location();
    std::string text = "";

    while (  !this->eof()
          && (  std::isalnum(this->peek_char()) != 0
             || this->peek_char() == '_'))
    {
        text += this->get_char();
    }

    if (text == "if")
    {
        return Token(Token::Kind::KwIf, location);
    }
    if (text == "else") {
        return Token(Token::Kind::KwElse, location);
    }
    if (text == "do")
    {
        return Token(Token::Kind::KwDo, location);
    }
    if (text == "while")
    {
        return Token(Token::Kind::KwWhile, location);
    }
    if (text == "for") {
        return Token(Token::Kind::KwFor, location);
    }
    if (text == "loop") {
        return Token(Token::Kind::KwLoop, location);
    }
    if (text == "continue")
    {
        return Token(Token::Kind::KwContinue, location);
    }
    if (text == "break")
    {
        return Token(Token::Kind::KwBreak, location);
    }
    if (text == "return")
    {
        return Token(Token::Kind::KwReturn, location);
    }
     if (text == "enum")
    {
        return Token(Token::Kind::KwEnum, location);
    }
    if (text == "struct")
    {
        return Token(Token::Kind::KwStruct, location);
    }
    if (text == "union")
    {
        return Token(Token::Kind::KwUnion, location);
    }
    if (text == "typedef")
    {
        return Token(Token::Kind::KwTypedef, location);
    }
    if (text == "extern") {
        return Token(Token::Kind::KwExtern, location);
    }
    if (text == "static")
    {
        return Token(Token::Kind::KwStatic, location);
    }
    if (text == "const")
    {
        return Token(Token::Kind::KwConst, location);
    }

    return Token(Token::Kind::Identifier, location, text);
}

std::vector<Token> Lexer::collect()
{
    std::vector<Token> result;

    while (!this->eof())
    {
        result.push_back(this->get());
    }
    
    return result;
}

void Lexer::dump_tokens(std::ostream &os, std::vector<Token> const& tokens)
{
    for (auto& token: tokens)
    {
        os << token << "\n";
    }
}

}  // namespace altercc
