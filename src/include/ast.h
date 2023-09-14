#pragma once

#include <string>
#include <vector>

enum OP {
    ADD,
    SUB,
    MUL,
    DIV,
};

namespace AST {
class AST {};
class Expression : private AST {
  public:
    Expression *lhs;
    Expression *rhs;
    OP *op;
};
class Term : private Expression {};
class StringLiteral : private Term {
  public:
    std::string value;
};
class IntegerLiteral : private Term {
  public:
    int value;
};

class Identifier : private Term {
  public:
    std::string value;
};
class Assignment {
  public:
    std::string variableName;
    Expression *value;
};
class Statement {};
class Compound {
  public:
    std::vector<Statement> statements;
};
} // namespace AST
