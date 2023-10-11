#pragma once

#include "token.hpp"
#include <string>

class Lexer {
    std::string source;
    char character;
    int line = 0;
    int column = 0;
    size_t index = 0;

  public:
    Lexer(std::string source);
    Token *nextToken();
    Token *lexIdentifier();
    Token *lexInt();
    Token *lexString();
    Token *advanceWith(Token *token);
    Token *advanceWith(TokenType type);
    void skipWhitespace();
    void skipComments();
    void advance();
    char peek(int offset);
};
