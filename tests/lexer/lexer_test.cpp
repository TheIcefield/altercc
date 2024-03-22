#include <altercc/lexer/Lexer.hpp>

#include <gtest/gtest.h>

#include <sstream>

TEST(LexerTest, TokenKindTest)
{
    std::stringstream input("int i = 10;\n    12 <= 12.4 >  {hello[world)");

    altercc::Lexer lexer(input, false);
    
    auto token = lexer.get();
    EXPECT_EQ(token.get_kind(), altercc::Token::Kind::Identifier);
    EXPECT_EQ(token.get_lexem(), "int");

    token = lexer.get();
    EXPECT_EQ(token.get_kind(), altercc::Token::Kind::Identifier);
    EXPECT_EQ(token.get_lexem(), "i");

    EXPECT_EQ(lexer.get().get_kind(), altercc::Token::Kind::Assign);

    token = lexer.get();
    EXPECT_EQ(token.get_kind(), altercc::Token::Kind::Integer);
    EXPECT_EQ(token.get_lexem(), "10");

    EXPECT_EQ(lexer.get().get_kind(), altercc::Token::Kind::Semicolon);

    token = lexer.get();
    EXPECT_EQ(token.get_kind(), altercc::Token::Kind::Integer);
    EXPECT_EQ(token.get_lexem(), "12");

    EXPECT_EQ(lexer.get().get_kind(), altercc::Token::Kind::Lte);

    token = lexer.get();
    EXPECT_EQ(token.get_kind(), altercc::Token::Kind::Decimal);
    EXPECT_EQ(token.get_lexem(), "12.4");

    EXPECT_EQ(lexer.get().get_kind(), altercc::Token::Kind::Gt);
    EXPECT_EQ(lexer.get().get_kind(), altercc::Token::Kind::Lcb);

    token = lexer.get();
    EXPECT_EQ(token.get_kind(), altercc::Token::Kind::Identifier);
    EXPECT_EQ(token.get_lexem(), "hello");

    EXPECT_EQ(lexer.get().get_kind(), altercc::Token::Kind::Lsb);

    token = lexer.get();
    EXPECT_EQ(token.get_kind(), altercc::Token::Kind::Identifier);
    EXPECT_EQ(token.get_lexem(), "world");

    EXPECT_EQ(lexer.get().get_kind(), altercc::Token::Kind::Rparen);
}
