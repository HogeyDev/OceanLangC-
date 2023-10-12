#pragma once

#include "ast.hpp"
#include "debug.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include <iostream>
#include <variant>
#include <vector>

class Parser {
    std::vector<Token*> tokenList;
    size_t tokenIndex;
    Token* currentToken;

public:
    Parser(std::vector<Token*> tokenList) {
        this->tokenList = tokenList;
        this->tokenIndex = 0;
        this->currentToken = this->tokenList[this->tokenIndex];
        // std::cout << getPrintableToken(this->currentToken) << std::endl;
    }
    void errorOut(TokenType type) {
        std::cerr << "Expected Token Of Type: " << getTokenType(type)
                  << ", But Instead Got Type: "
                  << getTokenType(this->currentToken->type) << std::endl;
        std::cerr << "\tCurrent Token: "
                  << getPrintableToken(this->currentToken) << std::endl;
        exit(1);
    }
    Token* peekToken(size_t offset = 0) {
        if (this->tokenIndex + offset >= this->tokenList.size())
            return new Token("", TokenType::ENDOFFILE);
        return this->tokenList[this->tokenIndex + offset];
    }
    Token* nextToken() {
        this->tokenIndex++;
        this->currentToken = this->peekToken();
        // std::cout << getPrintableToken(this->currentToken) << std::endl;
        return this->currentToken;
    }
    Token* consume(TokenType type) {
        if (this->currentToken->type != type)
            this->errorOut(type);
        this->nextToken();
        return this->currentToken;
    };
    AST::Program* parse() {
        AST::Program* ret = new AST::Program();
        ret->scope = this->parseScope();
        return ret;
    }
    AST::Scope* parseScope() {
        bool isDelimitedByBraces =
            (this->currentToken->type == TokenType::LBRACE);
        if (isDelimitedByBraces)
            this->consume(TokenType::LBRACE);
        AST::Scope* scope = new AST::Scope();
        while (this->currentToken->type != TokenType::ENDOFFILE) {
            AST::Statement* statement = new AST::Statement();
            if (this->currentToken->type == TokenType::IDENTIFIER &&
                this->peekToken(1)->type == TokenType::IDENTIFIER &&
                this->peekToken(2)->type == TokenType::EQUALS) {
                if (this->currentToken->value == "extern") {
                    // Extern Statement
                    AST::Extern* ast = new AST::Extern();
                    this->consume(TokenType::IDENTIFIER);
                    ast->language = this->currentToken->value;
                    this->consume(TokenType::IDENTIFIER);
                    this->consume(TokenType::EQUALS);
                    ast->code = this->currentToken->value;
                    this->consume(TokenType::STRING);
                    statement->var = ast;
                } else {
                    // Variable Assignment
                    AST::VariableAssignment* ast =
                        new AST::VariableAssignment();
                    ast->type = getPrimType(this->currentToken->value);
                    this->consume(TokenType::IDENTIFIER);
                    ast->variableName = new AST::Identifier();
                    ast->variableName->value = this->currentToken->value;
                    this->consume(TokenType::IDENTIFIER);
                    this->consume(TokenType::EQUALS);
                    ast->value = this->parseExpression();
                    statement->var = ast;
                }
            } else if (this->currentToken->type == TokenType::IDENTIFIER &&
                       this->peekToken(1)->type == TokenType::IDENTIFIER &&
                       this->peekToken(2)->type == TokenType::LPAREN) {
                // function declaration
                AST::FunctionDeclaration* ast = new AST::FunctionDeclaration();
                ast->type = getPrimType(this->currentToken->value);
                this->consume(TokenType::IDENTIFIER);
                ast->functionName = new AST::Identifier();
                ast->functionName->value = this->currentToken->value;
                this->consume(TokenType::IDENTIFIER);
                this->consume(TokenType::LPAREN);
                // parse arguments right here (when i want to ofc)
                this->consume(TokenType::RPAREN);
                ast->value = this->parseScope();
                statement->var = ast;
            } else if (this->currentToken->value == "import") {
                AST::Import* ast = new AST::Import();
                this->consume(TokenType::IDENTIFIER);
                ast->filePath = this->currentToken->value;
                this->consume(TokenType::STRING);
                statement->var = ast;
            } else if (this->currentToken->type == TokenType::IDENTIFIER &&
                       this->peekToken(1)->type == TokenType::LPAREN) {
                // function call
                AST::FunctionCall* ast = new AST::FunctionCall();
                AST::Identifier* name = new AST::Identifier();
                name->value = this->currentToken->value;
                ast->functionName = name;
                this->consume(TokenType::IDENTIFIER);
                this->consume(TokenType::LPAREN);
                ast->arguments = this->parseArguments();
                this->consume(TokenType::RPAREN);
                this->consume(TokenType::SEMICOLON);
                statement->var = ast;
            } else if (this->currentToken->type == TokenType::RBRACE &&
                       isDelimitedByBraces) {
                this->consume(TokenType::RBRACE);
                break;
            } else {
                std::cerr << "No matching AST parse method for token: "
                          << getPrintableToken(this->currentToken) << std::endl;
                exit(1);
            }
            scope->statements.push_back(statement);
        }
        return scope;
    }
    std::vector<AST::Expression*> parseArguments() {
        std::vector<AST::Expression*> arguments;

        bool stillParsingArguments = true;
        while (stillParsingArguments) {

            AST::Expression* argument = this->parseExpression();
            if (this->currentToken->type == TokenType::COMMA) {
                this->consume(TokenType::COMMA);
            } else {
                stillParsingArguments = false;
            }
            arguments.push_back(argument);
        }

        return arguments;
    }
    AST::Expression* parseExpression(int minimumPrecedence = 0) {
        AST::Term* lhsTerm = this->parseTerm();
        AST::Expression* lhsExpression = new AST::Expression();
        lhsExpression->var = lhsTerm;

        if (this->currentToken->type == TokenType::SEMICOLON) {
            // just a number
            this->consume(TokenType::SEMICOLON);
            return lhsExpression;
        }

        while (true) {
            int precedence = getOperatorPrecedence(this->currentToken->value);

            if (!isBinaryOperation(this->currentToken->value) ||
                precedence < minimumPrecedence) {
                break;
            }

            OP operation = getOperation(this->currentToken->type);
            this->nextToken();
            int nextMinimumPrecedence = precedence + 1;

            AST::Expression* rhsExpression =
                this->parseExpression(nextMinimumPrecedence);
            AST::BinaryExpression* binaryExpression =
                new AST::BinaryExpression();
            AST::Expression* binaryExpressionLhs = new AST::Expression();

            binaryExpressionLhs->var = lhsExpression->var;
            binaryExpression->operation = operation;
            binaryExpression->lhs = binaryExpressionLhs;
            binaryExpression->rhs = rhsExpression;

            lhsExpression->var = binaryExpression;
        }
        return lhsExpression;
    }
    AST::Term* parseTerm() {
        AST::Term* ast = new AST::Term();

        if (this->currentToken->type == TokenType::INTLIT) {
            AST::IntegerLiteral* integerLiteral = new AST::IntegerLiteral();
            integerLiteral->value = stoi(this->currentToken->value);
            this->consume(TokenType::INTLIT);
            ast->var = integerLiteral;
        } else if (this->currentToken->type == TokenType::STRING) {
            AST::StringLiteral* stringLiteral = new AST::StringLiteral();
            stringLiteral->value = this->currentToken->value;
            this->consume(TokenType::STRING);
            ast->var = stringLiteral;
        } else if (this->currentToken->type == TokenType::LPAREN) {
            this->consume(TokenType::LPAREN);
            AST::Expression* expression = this->parseExpression();
            this->consume(TokenType::RPAREN);
            ast->var = expression;
        } else if (this->currentToken->type == TokenType::IDENTIFIER) {
            AST::Identifier* identifier = new AST::Identifier();
            identifier->value = this->currentToken->value;
            this->consume(TokenType::IDENTIFIER);
            ast->var = identifier;
        } else {
            std::cerr << "Term Cannot Be Of Type: "
                      << getTokenType(this->currentToken->type) << std::endl;
            exit(1);
        }

        return ast;
    }
};
