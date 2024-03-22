#pragma once

#include <ostream>
#include <variant>

namespace altercc
{

struct Location
{
    std::size_t row_ = 1;
    std::size_t col_ = 1;
};

class Token {
public:
    enum class Kind {
    /* Having lexem tokens */
        Identifier,
        Text,
        Integer,
        Decimal,

    /* Key words */
        KwIf,
        KwElse,
        KwDo,
        KwWhile,
        KwFor,
        KwLoop,
        KwContinue,
        KwBreak,
        KwReturn,
        KwStruct,
        KwUnion,
        KwEnum,
        KwTypedef,
        KwExtern,
        KwStatic,
        KwConst,

    /* Other tokens */
        Arrow,        // '->'
        Dot,          // '.'
        Comma,        // ','
        Colon,        // ':'
        Semicolon,    // ';'
        Lparen,       // '('
        Rparen,       // ')'
        Lcb,          // '{'
        Rcb,          // '}'
        Lsb,          // '['
        Rsb,          // ']'
        Lshift,       // '<<'
        Rshift,       // '>>'
        Lt,           // '<'
        Lte,          // '<='
        Gt,           // '>'
        Gte,          // '>='
        Eq,           // '=='
        Neq,          // '!='
        Assign,       // '='
        Plus,         // '+'
        Minus,        // '-'
        Div,          // '/'
        Mod,          // '%'
        Mul,          // '*'
        BitwiseXor,   // '^'
        BitwiseAnd,   // '&'
        BitwiseOr,    // '|'
        LogicAnd,     // '&&'
        LogicOr,      // '||'
        AddAssign,    // '+='
        SubAssign,    // '-='
        MulAssign,    // '*='
        DivAssign,    // '/='
        ModAssign,    // '%='
        AndAssign,    // '&='
        OrAssign,     // '|='
        XorAssign,    // '^='
        LshiftAssign, // '<<='
        RshiftAssign, // '>>='
        Not,          // '!'
        Tilda,        // '~'

        Eof,
        Unknown,
    };

    Token() = default;

    Token(Kind const kind, Location const location, std::string const lexem = "")
        : kind_{kind}
        , location_{location}
        , lexem_{lexem}
    {
    }

    Kind get_kind() const { return kind_; }
    Location get_location() const { return location_; }
    std::string const& get_lexem() const { return lexem_; }

    static std::string kind_to_string(Kind const kind);

private:
    Kind        kind_;
    Location    location_;
    std::string lexem_;
};

std::ostream& operator<<(std::ostream& os, Location const &location);
std::ostream& operator<<(std::ostream& os, Token const &token);

bool operator==(Location const &lhs, Location const &rhs);
bool operator!=(Location const &lhs, Location const &rhs);

bool operator==(Token const &lhs, Token const &rhs);
bool operator!=(Token const &lhs, Token const &rhs);

} // namespace altercc
