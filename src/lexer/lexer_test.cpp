#include <gtest/gtest.h>
#include "../utilities/logging/logger_manager/logger_manager.h"
#include "../utilities/logging/console_logger/console_logger.h"
#include "lexer.h"


Token createToken(Token::TokenType type, const std::string& literal = "") {
        return Token{0, 0, type, literal};
}

TEST(LexerTest, SingleCharsLexTest) {
    Lexer lex("* + - / = > < ! . { } ( )");

    std::vector<Token> checkSequence = {
         createToken(Token::STAR, "*"),
        createToken(Token::PLUS, "+"),
        createToken(Token::MINUS, "-"),
        createToken(Token::SLASH, "/"),
        createToken(Token::EQ, "="),
        createToken(Token::GT, ">"),
        createToken(Token::LT, "<"),
        createToken(Token::EXCLAMATION, "!"),
        createToken(Token::DOT, "."),
        createToken(Token::L_CURL_BRACE, "{"),
        createToken(Token::R_CURL_BRACE, "}"),
        createToken(Token::L_BRACE, "("),
        createToken(Token::R_BRACE, ")"),
    };

    for(auto& tok: checkSequence) {
        Token toEq = lex.next();
        ASSERT_EQ(tok.literal, toEq.literal);
        ASSERT_EQ(tok.tokenType, toEq.tokenType);
    }
}

TEST(LexerTest, CombinationCharsLexTest) {
    Lexer lex("-> == != >= <= && ||");

    std::vector<Token> checkSequence = {
        createToken(Token::ARROW, "->"),
        createToken(Token::DOUBLE_EQ, "=="),
        createToken(Token::NEQ, "!="),
        createToken(Token::GTE, ">="),
        createToken(Token::LTE, "<="),
        createToken(Token::AND, "&&"),
        createToken(Token::OR, "||"),
    };

    for(auto& tok: checkSequence) {
        Token toEq = lex.next();
        ASSERT_EQ(tok.literal, toEq.literal);
        ASSERT_EQ(tok.tokenType, toEq.tokenType);
    }
}

TEST(LexerTest, ReservedLexemsLexTest) {
    Lexer lex("fn if else pub Int Float Char Bool true false");

    std::vector<Token> checkSequence = {
        createToken(Token::FUNC_LITERAL, "fn"),
        createToken(Token::IF, "if"),
        createToken(Token::ELSE, "else"),
        createToken(Token::PUBLIC, "pub"),
        createToken(Token::INT_TYPE, "Int"),
        createToken(Token::FLOAT_TYPE, "Float"),
        createToken(Token::CHAR_TYPE, "Char"),
        createToken(Token::BOOL_TYPE, "Bool"),
        createToken(Token::BOOL, "true"),
        createToken(Token::BOOL, "false"),
    };

    for(auto& tok: checkSequence) {
        Token toEq = lex.next();
        ASSERT_EQ(tok.literal, toEq.literal);
        ASSERT_EQ(tok.tokenType, toEq.tokenType);
    }
}

TEST(LexerTest, NumericLexTest) {
    Lexer lex("10 10.0 1000000 122312341231 1.31231 0.2123123");

    std::vector<Token> checkSequence = {
        createToken(Token::INTEGER, "10"),
        createToken(Token::FLOAT, "10.0"),
        createToken(Token::INTEGER, "1000000"),
        createToken(Token::INTEGER, "122312341231"),
        createToken(Token::FLOAT, "1.31231"),
        createToken(Token::FLOAT, "0.2123123"),
    };

    for(auto& tok: checkSequence) {
        Token toEq = lex.next();
        ASSERT_EQ(tok.literal, toEq.literal);
        ASSERT_EQ(tok.tokenType, toEq.tokenType);
    }
}