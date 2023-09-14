#pragma once

#include <string>

enum TokenType {
  IDENTIFIER,
  INT,
  STRING,
  LBRACE,
  RBRACE,
  LPAREN,
  RPAREN,
  SEMICOLON,
  ENDOFFILE,
  EMPTY,
  STAR,
  PLUS,
  MINUS,
  SLASH,
  EQUALS,
};

class Token {
public:
  std::string value;
  TokenType type;

  Token(std::string value, TokenType type) {
    this->value = value;
    this->type = type;
  }
};

std::string getTokenType(TokenType type);
std::string getPrintableToken(Token *token);
