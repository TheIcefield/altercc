#include "Token.hpp"

namespace altercc
{

std::string Token::kind_to_string(Token::Kind const kind)
{
    switch (kind)
    {
        case Token::Kind::Identifier: return "ID";
        case Token::Kind::Integer: return "integer";
        case Token::Kind::Decimal: return "decimal";
        case Token::Kind::Text: return "text";
        case Token::Kind::KwIf: return "if";
        case Token::Kind::KwElse: return "else";
        case Token::Kind::KwDo: return "do";
        case Token::Kind::KwWhile: return "while";
        case Token::Kind::KwFor: return "for";
        case Token::Kind::KwLoop: return "loop";
        case Token::Kind::KwContinue: return "continue";
        case Token::Kind::KwBreak: return "break";
        case Token::Kind::KwReturn: return "return";
        case Token::Kind::KwEnum: return "enum";
        case Token::Kind::KwStruct: return "struct";
        case Token::Kind::KwUnion: return "union";
        case Token::Kind::KwTypedef: return "typedef";
        case Token::Kind::KwExtern: return "extern";
        case Token::Kind::KwStatic: return "static";
        case Token::Kind::KwConst: return "const";
        case Token::Kind::Arrow: return "->";
        case Token::Kind::Dot: return ".";
        case Token::Kind::Comma: return ",";
        case Token::Kind::Colon: return ":";
        case Token::Kind::Semicolon: return ";";
        case Token::Kind::Lparen: return "(";
        case Token::Kind::Rparen: return ")";
        case Token::Kind::Lcb: return "{";
        case Token::Kind::Rcb: return "}";
        case Token::Kind::Lsb: return "[";
        case Token::Kind::Rsb: return "]";
        case Token::Kind::Lshift: return "<<";
        case Token::Kind::Rshift: return ">>";
        case Token::Kind::Lt: return "<";
        case Token::Kind::Lte: return "<=";
        case Token::Kind::Gt: return ">";
        case Token::Kind::Gte: return ">=";
        case Token::Kind::Eq: return "==";
        case Token::Kind::Neq: return "!=";
        case Token::Kind::Assign: return "=";
        case Token::Kind::Plus: return "+";
        case Token::Kind::Minus: return "-";
        case Token::Kind::Div: return "/";
        case Token::Kind::Mod: return "%";
        case Token::Kind::Mul: return "*";
        case Token::Kind::BitwiseXor: return "^";
        case Token::Kind::BitwiseAnd: return "&";
        case Token::Kind::BitwiseOr: return "|";
        case Token::Kind::LogicAnd: return "&&";
        case Token::Kind::LogicOr: return "||";
        case Token::Kind::AddAssign: return "+=";
        case Token::Kind::SubAssign: return "-=";
        case Token::Kind::MulAssign: return "*=";
        case Token::Kind::DivAssign: return "/=";
        case Token::Kind::ModAssign: return "%=";
        case Token::Kind::AndAssign: return "&=";
        case Token::Kind::OrAssign: return "|=";
        case Token::Kind::XorAssign: return "^=";
        case Token::Kind::LshiftAssign: return "<<=";
        case Token::Kind::RshiftAssign: return ">>=";
        case Token::Kind::Not: return "!";
        case Token::Kind::Tilda: return "~";
        case Token::Kind::Eof: return "EOF";
    }

    return "unknown";
}

std::ostream& operator<<(std::ostream &os, Location const &location)
{
    os << '[' << location.row_ << ':' << location.col_ << ']';
    return os;
}

std::ostream& operator<<(std::ostream &os, Token const &token) {
    os << token.get_location() << " \'" << Token::kind_to_string(token.get_kind()) << "\'";

    switch (token.get_kind())
    {
        case Token::Kind::Identifier:
        case Token::Kind::Integer:
        case Token::Kind::Decimal:
        case Token::Kind::Text:
        case Token::Kind::Unknown:
        {
            os << ": \"" << token.get_lexem() << "\"";
        }
    }

    return os;
}

bool operator==(Location const &lhs, Location const &rhs)
{
    return (lhs.row_ == rhs.row_) && (lhs.col_ == rhs.col_);
}

bool operator!=(Location const &lhs, Location const &rhs)
{
    return !(lhs == rhs);
}

bool operator==(Token const &lhs, Token const &rhs)
{
    return    (lhs.get_kind() == rhs.get_kind())
           && (lhs.get_location() == rhs.get_location())
           && (lhs.get_lexem() == rhs.get_lexem());
}

bool operator!=(Token const &lhs, Token const &rhs)
{
    return !(lhs == rhs);
}

} // namespace altercc
