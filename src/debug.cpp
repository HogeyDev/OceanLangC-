#include "debug.hpp"
#include "ast.hpp"
#include <string>

namespace DEBUG {
std::string calculateTabs(int tabs) {
    std::string ret;
    for (int i = 0; i < tabs; i++)
        ret += "\t";
    return ret;
}

std::string getPrintableIdentifier(AST::Identifier* ast, int tabs) {
    return calculateTabs(tabs) + "Identifier(value: " + ast->value + ")";
}

std::string getPrintableImport(AST::Import* ast, int tabs) {
    return calculateTabs(tabs) + "Import(filePath: " + ast->filePath + ")";
}

std::string getPrintableExtern(AST::Extern* ast, int tabs) {
    return calculateTabs(tabs) + "Extern(language: " + ast->language + "\n" +
           calculateTabs(tabs + 1) + "code: " + ast->code + ")";
}

std::string getPrintableFunctionDeclaration(AST::FunctionDeclaration* ast,
                                            int tabs) {
    return calculateTabs(tabs) + "FunctionDeclaration(functionName:\n" +
           getPrintableIdentifier(ast->functionName, tabs + 1) + "\n" +
           calculateTabs(tabs + 1) +
           "type: " + getPrintablePrimType(ast->type) + "\n" +
           calculateTabs(tabs + 1) + "value:\n" +
           getPrintableScope(ast->value, tabs + 2) + "\n" +
           calculateTabs(tabs) + ")";
}

std::string getPrintableIntegerLiteral(AST::IntegerLiteral* ast, int tabs) {
    return calculateTabs(tabs) +
           "IntegerLiteral(value: " + std::to_string(ast->value) + ")";
}

std::string getPrintableStringLiteral(AST::StringLiteral* ast, int tabs) {
    return calculateTabs(tabs) + "StringLiteral(value: " + ast->value + ")";
}

std::string getPrintableTerm(AST::Term* ast, int tabs) {
    std::string ret;
    struct TermVisitor {
        std::string& ret;
        int tabs;
        void operator()(AST::IntegerLiteral* ast) {
            ret += getPrintableIntegerLiteral(ast, tabs);
        }
        void operator()(AST::Identifier* ast) {
            ret += getPrintableIdentifier(ast, tabs);
        }
        void operator()(AST::StringLiteral* ast) {
            ret += getPrintableStringLiteral(ast, tabs);
        }
        void operator()(AST::Expression* ast) {
            ret += getPrintableExpression(ast, tabs);
        }
    };
    TermVisitor visitor = {.ret = ret, .tabs = tabs};
    std::visit(visitor, ast->var);
    return ret;
}

std::string getPrintableBinaryExpression(AST::BinaryExpression* ast, int tabs) {
    return "BINARYEXPR";
}

std::string getPrintableExpression(AST::Expression* ast, int tabs) {
    std::string ret;
    struct ExpressionVisitor {
        std::string& ret;
        int tabs;
        void operator()(AST::Term* ast) { ret += getPrintableTerm(ast, tabs); }
        void operator()(AST::BinaryExpression* ast) {
            ret += getPrintableBinaryExpression(ast, tabs);
        }
    };
    ExpressionVisitor visitor = {.ret = ret, .tabs = tabs};
    std::visit(visitor, ast->var);
    return ret;
}

std::string getPrintableVariableAssignment(AST::VariableAssignment* ast,
                                           int tabs) {
    return calculateTabs(tabs) + "VariableAssignment(variableName:\n" +
           calculateTabs(tabs + 1) + getPrintableIdentifier(ast->variableName) +
           "\n" + calculateTabs(tabs + 1) +
           "type: " + getPrintablePrimType(ast->type) + "\n" +
           calculateTabs(tabs + 1) + "value:\n" +
           getPrintableExpression(ast->value, tabs + 2) + "\n" +
           calculateTabs(tabs) + ")";
}

std::string getPrintableArgument(AST::Expression* ast, int tabs) {
    return getPrintableExpression(ast, tabs);
}

std::string getPrintableFunctionCall(AST::FunctionCall* ast, int tabs) {
    std::string ret = calculateTabs(tabs) + "FunctionCall(functionName:\n" +
                      getPrintableIdentifier(ast->functionName, tabs + 1) +
                      "\n" + calculateTabs(tabs + 1) + "arguments:\n";
    for (unsigned int i = 0; i < ast->arguments.size(); i++) {
        ret += getPrintableArgument(ast->arguments[i], tabs + 2) + "\n";
    }
    ret += calculateTabs(tabs) + ")";
    return ret;
}

std::string getPrintableStatement(AST::Statement* ast, int tabs) {
    std::string ret;
    // std::variant<VariableAssignment*, FunctionDeclaration*, FunctionCall*,
    // Import*>

    struct StatementVisitor {
        std::string& ret;
        int tabs;
        void operator()(AST::VariableAssignment* ast) {
            ret += getPrintableVariableAssignment(ast, tabs);
        }
        void operator()(AST::FunctionDeclaration* ast) {
            ret += getPrintableFunctionDeclaration(ast, tabs);
        }
        void operator()(AST::FunctionCall* ast) {
            ret += getPrintableFunctionCall(ast, tabs);
        }
        void operator()(AST::Import* ast) {
            ret += getPrintableImport(ast, tabs);
        }
        void operator()(AST::Extern* ast) {
            ret += getPrintableExtern(ast, tabs);
        }
    };
    StatementVisitor visitor = {.ret = ret, .tabs = tabs};
    std::visit(visitor, ast->var);
    return ret;
}

std::string getPrintableScope(AST::Scope* ast, int tabs) {
    std::string ret = calculateTabs(tabs) + "Scope(Statements:\n";
    for (unsigned int i = 0; i < ast->statements.size(); i++) {
        ret += getPrintableStatement(ast->statements[i], tabs + 1) + "\n";
    }
    ret += calculateTabs(tabs) + ")";
    return ret;
}

std::string getPrintableProgram(AST::Program* ast, int tabs) {
    return calculateTabs(tabs) + "Program(Scope:\n" +
           getPrintableScope(ast->scope, tabs + 1) + "\n" +
           calculateTabs(tabs) + ")";
}

} // namespace DEBUG
