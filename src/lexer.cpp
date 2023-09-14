#include "lexer.h"
#include "token.h"
#include <cctype>
#include <iostream>
#include <string>

Lexer::Lexer(std::string source) {
  this->source = source;
  this->character = this->source[0];
}

void Lexer::advance() {
  if (this->character != '\0') {
    if (this->character == '\n') {
      this->line++;
      this->column = 0;
    } else {
      this->column++;
    }
    this->character = this->source[++this->index];
  }
}

Token *Lexer::advanceWith(Token *token) {
  this->advance();
  return token;
}

Token *Lexer::advanceWith(TokenType type) {
  this->advance();
  return new Token("", type);
}

Token *Lexer::nextToken() {
  this->skipWhitespace();
  this->skipComments();

  if (std::isalpha(this->character))
    return this->lexIdentifier();

  if (std::isdigit(this->character))
    return this->lexInt();

  switch (this->character) {
  case '"':
    return this->advanceWith(this->lexString());
  case '(':
    return this->advanceWith(TokenType::LPAREN);
  case ')':
    return this->advanceWith(TokenType::RPAREN);
  case '{':
    return this->advanceWith(TokenType::LBRACE);
  case '}':
    return this->advanceWith(TokenType::RBRACE);
  case '+':
    return this->advanceWith(TokenType::PLUS);
  case '-':
    return this->advanceWith(TokenType::MINUS);
  case '*':
    return this->advanceWith(TokenType::STAR);
  case '/':
    return this->advanceWith(TokenType::SLASH);
  case '=':
    return this->advanceWith(TokenType::EQUALS);
  case ';':
    return this->advanceWith(TokenType::SEMICOLON);
  case '\0':
    return new Token("", TokenType::ENDOFFILE);
  default: {
    std::cerr << "Unknown Character: " << this->character << std::endl;
    std::cerr << "\tAt Location " << this->line + 1 << ":" << this->column + 1
              << std::endl;
    exit(1);
  }
  }
  return new Token("", TokenType::EMPTY);
}

Token *Lexer::lexIdentifier() {
  std::string value = "";
  while (std::isalpha(this->character)) {
    value.push_back(this->character);
    this->advance();
  }
  Token *ret = new Token(value, TokenType::IDENTIFIER);
  return ret;
}

Token *Lexer::lexInt() {
  std::string integer;
  while (std::isdigit(this->character)) {
    integer.push_back(this->character);
    this->advance();
  }
  Token *ret = new Token(integer, TokenType::INT);
  return ret;
}

Token *Lexer::lexString() {
  this->advance();
  std::string value;
  while (this->character != '"') {
    value.push_back(this->character);
    this->advance();
  }
  this->advance();
  return new Token(value, TokenType::STRING);
}

void Lexer::skipWhitespace() {
  while (std::isspace(this->character)) {
    this->advance();
  }
}

void Lexer::skipComments() {
  if (this->character == '/' && (this->peek(1) == '/')) {
    while (this->character != '\n')
      this->advance();
  }
  this->skipWhitespace();
}

char Lexer::peek(int offset = 0) {
  if (this->index + offset >= this->source.size()) {
    return '\0';
  } else {
    return this->source[this->index + offset];
  }
}
