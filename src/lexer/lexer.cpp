#include "lexer.h"
#include <map>

std::map<std::string, Token::TokenType> reservedTokens = {
    {"fn", Token::FUNC_LITERAL},
    {"pub", Token::PUBLIC},
    {"ret", Token::RETURN},
    {"if", Token::IF},
    {"else", Token::ELSE},
    {"Int", Token::INT_TYPE},
    {"Float", Token::FLOAT_TYPE},
    {"Char", Token::CHAR_TYPE},
    {"Bool", Token::BOOL_TYPE},
};

Token Lexer::parseNumber() {
    size_t start = currentIndex;
    bool isFloat = false;

    while (isdigit(currentChar()) || currentChar() == '.') {
        if (currentChar() == '.') {
            if (isFloat) break; 
            isFloat = true;
        }
        advanceChar();
    }

    std::string number = textToParse.substr(start, currentIndex - start);

    return isFloat ? createToken(Token::FLOAT, number) : createToken(Token::INTEGER, number);
}

Token Lexer::parseIdentificator() {
    size_t start = currentIndex;

    while (isalnum(currentChar()) || currentChar() == '_') {
         advanceChar();
    }

    std::string ident = textToParse.substr(start, currentIndex - start);

    if (ident == "true" || ident == "false") {
        return createToken(Token::BOOL, ident);
    }

    auto it = reservedTokens.find(ident);

    if (it != reservedTokens.end()) {
        return createToken(it->second, ident);
    }

    return createToken(Token::IDENTIFICATOR, ident);
}

bool Lexer::parseUnaryOrCombinationOfChars(char curr) {
    switch (curr) {
        case '+': {
            currentToken = createToken(Token::PLUS, "+");
        } break; 
        case '-': {
            if (peekChar() == '>') {
                currentToken = createToken(Token::ARROW, "->");
                advanceChar();
            } else { currentToken = createToken(Token::MINUS, "-"); }
        } break;
        case '/': {
            currentToken = createToken(Token::SLASH, "/");
        } break; 
        case '*': {
            currentToken = createToken(Token::STAR, "*");
        } break; 
        case '=': {
            if (peekChar() == '=') {
                currentToken = createToken(Token::DOUBLE_EQ, "==");
                advanceChar();
            } 
            else { currentToken = createToken(Token::EQ, "="); }
        } break; 
        case '<': {
            if (peekChar() == '=') {
                currentToken = createToken(Token::LTE, "<=");
                advanceChar();
            } else { currentToken = createToken(Token::LT, "<"); }
        } break; 
        case '>': {
            if (peekChar() == '=') {
                currentToken = createToken(Token::GTE, ">=");
                advanceChar();
            } else { currentToken = createToken(Token::GT, ">"); }
        } break; 
        case '.': {
            currentToken = createToken(Token::DOT, ".");
        } break; 
        case '!': {
            if (peekChar() == '=') {
                currentToken = createToken(Token::NEQ, "!=");
                advanceChar();
            } else { currentToken = createToken(Token::EXCLAMATION, "!"); }
        } break; 
        case '{': currentToken = createToken(Token::L_CURL_BRACE, "{"); break; 
        case '}': currentToken = createToken(Token::R_CURL_BRACE, "}"); break; 
        case '(': currentToken = createToken(Token::L_BRACE, "("); break; 
        case ')': currentToken = createToken(Token::R_BRACE, ")"); break; 
        case ';': currentToken = createToken(Token::SEMICOLON, ";"); break; 
        case '&': {
            if (peekChar() == '&') {
                currentToken = createToken(Token::AND, "&&");
                advanceChar();
            } 
        } break; 
         case '|': {
            if (peekChar() == '|') {
                currentToken = createToken(Token::OR, "||");
                advanceChar();
            } 
        } break;
        default:
            return false;
    }

    advanceChar();

    return true;
}

Token const& Lexer::next() {
    skipWhitespace();

    char ch = currentChar();
    if (ch == '\0') {
        throw std::runtime_error("End of input");
    }

    if (parseUnaryOrCombinationOfChars(ch)) {
        return currentToken;
    }

    if (isdigit(ch)) {
        currentToken = parseNumber();
    } else if (isalpha(ch) || ch == '_') {
        currentToken = parseIdentificator();
    } else {
        throw std::runtime_error(std::string("Unexpected character: ") + ch);
    }

    return currentToken;
}

Token const& Lexer::peek() {

    size_t savedIndex = currentIndex;
    int savedRow = row;
    int savedCol = col;
    Token savedToken = currentToken;

    next();

    currentIndex = savedIndex;
    row = savedRow;
    col = savedCol;
    currentToken = savedToken;

    return currentToken;
}