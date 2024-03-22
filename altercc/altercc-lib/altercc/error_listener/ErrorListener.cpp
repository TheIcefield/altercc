#include "ErrorListener.hpp"

namespace altercc {

std::ostream& operator<<(std::ostream& os, Error const &error)
{
    os << "[" << error.location_.row_ << ":" << error.location_.col_ << "]: "
       << error.message_;
    return os;
}

Error& operator<<(Error &error, std::string const &message)
{
    error.message_ += message;
    return error;
}

Error& operator<<(Error &error, char const ch)
{
    error.message_ += ch;
    return error;
}

Error& operator<<(Error &error, Token const &token)
{
    switch (token.get_kind())
    {
        case Token::Kind::Identifier:
        case Token::Kind::Integer:
        case Token::Kind::Decimal:
        case Token::Kind::Text:
        case Token::Kind::Unknown:
        {
            error << "\"" << token.get_lexem() << "\"";
            break;
        }
        default:
        {
            error << "\"" << Token::kind_to_string(token.get_kind()) << "\"";
        }
    }

    return error;
}

void ErrorListener::error(Location const     location,
                          std::string const &message)
{
    this->errors_.emplace_back(Error
    {
        location,
        "Error: " + message
    });
}

void ErrorListener::warning(Location const     location,
                            std::string const &message)
{
    this->errors_.emplace_back(Warning
    {
        location,
        "Warning: " + message
    });
}

} // namespace altercc
