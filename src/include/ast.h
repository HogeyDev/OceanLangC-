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
class Expression {
public:
  Expression *lhs;
  Expression *rhs;
  OP *op;
};
class Term {};
class StringLiteral {
public:
  std::string value;
};
class IntegerLiteral {
public:
  int value;
};

class Identifier {
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
