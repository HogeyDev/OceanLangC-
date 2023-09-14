#pragma once

#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <iostream>
#include <variant>

class Parser {
  Lexer *lexer;
  Token *currentToken;

public:
  Parser(Lexer *lexer) { this->lexer = lexer; }
  void errorOut(TokenType type) {
    std::cerr << "Expected Token Of Type: " << getTokenType(this->currentToken->type)
              << ", But Instead Got Type: " << getTokenType(type) << std::endl;
    exit(1);
  }
  Token *eat(TokenType type) {
    if (this->currentToken->type != type)
      this->errorOut(type);

    this->currentToken = this->lexer->nextToken();
    return this->currentToken;
  };
  AST::Compound *parse() { return this->parseCompound(); }
  AST::Compound *parseCompound() {
    AST::Compound *ret = new AST::Compound();
    while ((this->currentToken = this->lexer->nextToken())->type != TokenType::ENDOFFILE) {
      switch (this->currentToken->type) {
      case TokenType::IDENTIFIER:
        ret->statements->push_back(this->parseIdentifier());
        break;
      default: {
        std::cerr << "Can't parse token: " << getPrintableToken(this->currentToken) << std::endl;
        exit(1);
      }
      }
    }
    return ret;
  }
  AST::Identifier *parseIdentifier() {}
};
