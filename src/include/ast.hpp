#pragma once

#include "token.hpp"
#include <ios>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

enum OP {
    ADD,
    SUB,
    MUL,
    DIV,
};

enum PrimType {
    INT,
    STR,
    VOID,
};

inline OP getOperation(std::string operation) {
    switch (operation[0]) {
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '*':
        return MUL;
    case '/':
        return DIV;
    default: {
        std::cerr << "Unknown Operator: " << operation << std::endl;
        exit(1);
    }
    }
}

inline OP getOperation(TokenType type) {
    switch (type) {
    case TokenType::PLUS:
        return ADD;
    case TokenType::MINUS:
        return SUB;
    case TokenType::STAR:
        return MUL;
    case TokenType::SLASH:
        return DIV;
    default: {
        std::cerr << "Unknown Operator: " << getTokenType(type) << std::endl;
        exit(1);
    }
    }
}

inline PrimType getPrimType(std::string value) {
    if (value == "int")
        return INT;
    else if (value == "str")
        return STR;
    else if (value == "void")
        return VOID;
    else {
        std::cerr << "Unknown type: " << value << std::endl;
        exit(1);
    }
}

inline std::string getPrintablePrimType(PrimType type) {
    static const std::string values[] = {
        "int",
        "str",
        "void",
    };
    return values[type];
}

inline bool isBinaryOperation(std::string value) {
    if (value.size() > 1)
        return 0;
    switch (value[0]) {
    case '+':
    case '-':
    case '*':
    case '/':
        return true;
    default:
        return false;
    }
}

inline int getOperatorPrecedence(std::string operation) {
    switch (operation[0]) {
    case '+':
    case '-':
    default:
        return 0;
    case '*':
    case '/':
        return 1;
    }
}

namespace AST {

class Program;
class Scope;
class Statement;
class VariableAssignment;
class VariableRecall;
class Expression;
class Term;
class BinaryExpression;
class FunctionDeclaration;
class FunctionCall;
class IntegerLiteral;
class Identifier;
class StringLiteral;
class Import;

class Program {
  public:
    Scope* scope;
};

class Scope {
  public:
    std::vector<Statement*> statements;
};

class Statement {
  public:
    std::variant<VariableAssignment*, FunctionDeclaration*, FunctionCall*, Import*> var;
};

class VariableAssignment {
  public:
    PrimType type;
    Identifier* variableName;
    Expression* value;
};

class VariableRecall {
  public:
    Identifier* variableName;
};

class Expression {
  public:
    std::variant<Term*, BinaryExpression*> var;
};

class Term {
  public:
    std::variant<IntegerLiteral*, Identifier*, StringLiteral*, Expression*, VariableRecall*> var;
};

class BinaryExpression {
  public:
    Expression* lhs;
    Expression* rhs;
    OP operation;
};

class FunctionDeclaration {
  public:
    PrimType type;
    Identifier* functionName;
    Scope* value;
};

class FunctionCall {
  public:
    Identifier* functionName;
    std::vector<Expression*> arguments;
};

class IntegerLiteral {
  public:
    int value;
};

class Identifier {
  public:
    std::string value;
};

class StringLiteral {
  public:
    std::string value;
};

class Import {
  public:
    std::string filePath;
};

} // namespace AST