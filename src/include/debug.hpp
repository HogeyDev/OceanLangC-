#pragma once
#include "ast.hpp"
#include <string>

namespace DEBUG {
std::string calculateTabs(int tabs = 0);
std::string getPrintableIdentifier(AST::Identifier* ast, int tabs = 0);
std::string getPrintableImport(AST::Import* ast, int tabs = 0);
std::string getPrintableFunctionDeclaration(AST::FunctionDeclaration* ast, int tabs = 0);
std::string getPrintableIntegerLiteral(AST::IntegerLiteral* ast, int tabs = 0);
std::string getPrintableStringLiteral(AST::StringLiteral* ast, int tabs = 0);
std::string getPrintableVariableRecall(AST::VariableRecall* ast, int tabs = 0);
std::string getPrintableTerm(AST::Term* ast, int tabs = 0);
std::string getPrintableBinaryExpression(AST::BinaryExpression* ast, int tabs = 0);
std::string getPrintableExpression(AST::Expression* ast, int tabs = 0);
std::string getPrintableVariableAssignment(AST::VariableAssignment* ast, int tabs = 0);
std::string getPrintableArgument(AST::Expression* ast, int tabs = 0);
std::string getPrintableFunctionCall(AST::FunctionCall* ast, int tabs = 0);
std::string getPrintableStatement(AST::Statement* ast, int tabs = 0);
std::string getPrintableScope(AST::Scope* ast, int tabs = 0);
std::string getPrintableProgram(AST::Program* ast, int tabs = 0);
} // namespace DEBUG