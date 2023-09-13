#include "lexer.h"
#include "token.h"
#include <cctype>
#include <iostream>
#include <string>

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
    if (this->character == ' ') {
        return;
    }
}

Token *Lexer::nextToken() {
    this->skipWhitespace();
    this->skipComments();

    if (std::isalpha(this->character)) {
        std::cout << "I'm an identifier!" << std::endl;
        Token *id = this->lexIdentifier();
        std::cout << id->value << std::endl;
        std::cout << getPrintableToken(id) << std::endl;
        return id;
    }

    switch (this->character) {
    case '\0':
        return new Token("", TokenType::ENDOFFILE);
        break;
    }
    return new Token("", TokenType::EMPTY);
}

Token *Lexer::lexIdentifier() {
    std::string value;
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
Token *Lexer::lexString() { return new Token("", TokenType::EMPTY); }

void Lexer::skipWhitespace() {
    while (std::isspace(this->character)) {
        this->advance();
    }
}

void Lexer::skipComments() {
    if (this->character == '/' && (this->peek(1) == '/')) {
        while (this->character != '\n')
            ;
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