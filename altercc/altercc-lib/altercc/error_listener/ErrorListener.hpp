#pragma once

#include "../lexer/Token.hpp"

#include <vector>
#include <string>

namespace altercc
{

struct Error
{
    Location    location_;
    std::string message_;
};

using Warning = Error;
using Errors = std::vector<Error>;
using Warnings = std::vector<Warning>;

std::ostream& operator<<(std::ostream& os, Error const &error);
Error& operator<<(Error &error, char const ch);
Error& operator<<(Error &error, std::string const &message);
Error& operator<<(Error &error, Token const &token);
Error& operator<<(Error &error, Token::Kind const &kind);

class ErrorListener
{
private:
    Errors   errors_{};
    Warnings warnings_{};

public:
    void error(Location const     location,
               std::string const &message);

    void warning(Location const     location,
                 std::string const &message);

    Errors const& errors() const { return this->errors_; }
    Warnings const& warnings() const { return this->warnings_; }
};

} // namespace altercc
