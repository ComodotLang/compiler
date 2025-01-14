#pragma once
#include <iostream>
#include <string.h>

#include "../utilities/logging/logger_manager/logger_manager.h"

struct Token {
    enum TokenType {
        PLUS = 0,
        MINUS,
        SLASH,
        STAR,
        DOUBLE_EQ,
        EQ,
        LT,
        GT,
        LTE,
        GTE,
        NEQ,
        DOT,
        EXCLAMATION,
        IDENTIFICATOR,

        INTEGER,
        FLOAT,
        CHAR,
        BOOL,

        FUNC_LITERAL,
        INT_TYPE,
        FLOAT_TYPE,
        CHAR_TYPE,
        BOOL_TYPE,

        L_CURL_BRACE,
        R_CURL_BRACE,

        L_BRACE,
        R_BRACE,

        SEMICOLON,

        RETURN,

        IF,
        ELSE,

        AND,
        OR,

        ARROW,

        PUBLIC,
        PRIVATE
    };

    int row, col;
    TokenType tokenType;
    std::string literal;
};

class Lexer {

    std::string textToParse;
    int row, col;
    size_t currentIndex;
    Token currentToken;

    char currentChar() const {
        return currentIndex < textToParse.size() ? textToParse[currentIndex] : '\0';
    }

    void advanceChar() {
        if (currentChar() == '\n') {
            row++;
            col = 0;
        } else {
            col++;
        }
        currentIndex++;
    }

    char peekChar() {
        advanceChar();
        int savedRow = row;
        int savedCol = col;
        int savedIndex = currentIndex;

        char ret = currentChar();

        row = savedRow;
        col = savedCol;
        currentIndex = savedIndex;

        return ret;
    }

    void skipWhitespace() {
        while (isspace(currentChar())) {
            advanceChar();
        }
    }

    Token createToken(Token::TokenType type, const std::string& literal = "") {
        return Token{row, col, type, literal};
    }

    Token parseNumber();
    Token parseIdentificator();
    bool parseUnaryOrCombinationOfChars(char curr);
public:
    Lexer(std::string text) : textToParse(std::move(text)), currentIndex(0), row(1), col(1) {}

    Token const& peek();

    Token const& next();
};