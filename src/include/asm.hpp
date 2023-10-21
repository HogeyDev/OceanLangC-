#pragma once

#include "ast.hpp"
#include "ocean.hpp"
#include <string>
#include <variant>

class AsmFrontend {
public:
    AST::Program* root;
    int stackSize;
    std::vector<std::string> variableNames;

    AsmFrontend(AST::Program* root) {
        this->root = root;
        this->stackSize = 0;
    }
    std::string compile() {
        std::string compiled;

        compiled += this->compileScope(this->root->scope);
        // compiled +=
        // 	"global _start\n"
        // 	"_start:"
        // 	"mov rax, 60\n"
        // 	"mov rdi, 69\n"
        // 	"syscall";
        return compiled;
    }
    std::string compileScope(AST::Scope* scope) {
        std::string compiled;

        for (unsigned int i = 0; i < scope->statements.size(); i++) {
            compiled += this->compileStatement(scope->statements.at(i));
        }

        return compiled;
    }
    std::string compileStatement(AST::Statement* statement) {
        std::string compiled;
        struct StatementVisitor {
            std::string& compiled;
            AsmFrontend* asmFrontend;
            void operator()(AST::VariableAssignment* variableAssignment) {
                if (variableAssignment->type == PrimType::INT) {
                    compiled += asmFrontend->compileExpression(
                        variableAssignment->value);
                } else if (variableAssignment->type == PrimType::STR) {
                    exit(101);
                } else {
                    std::cerr << "Unrecognized variable type: "
                              << getPrintablePrimType(variableAssignment->type)
                              << std::endl;
                    exit(1);
                }
                // compiled += asmFrontend->push("rax");
                asmFrontend->addVariable(
                    variableAssignment->variableName->value);
            }
            void operator()(AST::FunctionDeclaration* functionDeclaration) {
                compiled += "global " +
                            functionDeclaration->functionName->value + "\n" +
                            functionDeclaration->functionName->value + ":\n" +
                            "    push rbp\n    mov rbp, rsp\n";
                compiled +=
                    asmFrontend->compileScope(functionDeclaration->value);

                compiled += "    mov rsp, rbp\n    pop rbp\n    ret\n";
            }
            void operator()(AST::FunctionCall* functionCall) {
                for (unsigned int i = 0; i < functionCall->arguments.size();
                     i++) {
                    compiled += asmFrontend->compileExpression(
                        functionCall->arguments.at(i));
                }
                compiled +=
                    "    call " + functionCall->functionName->value + "\n";
            }
            void operator()(AST::Import* importStatement) {
                compiled += oceanCompile(importStatement->filePath);
            }
            void operator()(AST::Extern* externStatement) {
                if (externStatement->language == "asm")
                    compiled += externStatement->code;
                else {
                    std::cerr
                        << "No known way to process " +
                               externStatement->language + " language in extern"
                        << std::endl;
                    exit(1);
                }
            }
        };
        StatementVisitor visitor = {.compiled = compiled, .asmFrontend = this};
        std::visit(visitor, statement->var);
        return compiled;
    }
    std::string push(std::string registerName) {
        this->stackSize++;
        return "    push " + registerName + "\n";
    }
    std::string pop(std::string registerName) {
        this->stackSize--;
        return "    pop " + registerName + "\n";
    }
    std::string compileExpression(AST::Expression* expression) {
        std::string compiled;

        struct ExpressionVisitor {
            std::string& compiled;
            AsmFrontend* asmFrontend;
            void operator()(AST::Term* term) {
                compiled += asmFrontend->compileTerm(term);
            }
            void operator()(AST::BinaryExpression* binaryExpression) {
                exit(101);
            }
        };

        ExpressionVisitor visitor = {.compiled = compiled, .asmFrontend = this};
        std::visit(visitor, expression->var);

        return compiled;
    }
    std::string compileTerm(AST::Term* term) {
        std::string compiled;

        struct TermVisitor {
            std::string& compiled;
            AsmFrontend& asmFrontend;
            void operator()(AST::IntegerLiteral* integerLiteral) {
                compiled += "    mov rax, " +
                            std::to_string(integerLiteral->value) + "\n";
                compiled += asmFrontend.push("rax");
            }
            void operator()(AST::Identifier* identifier) {
                int index = asmFrontend.getVariableOffset(identifier->value);
                if (index < 0) {
                    std::cerr << "Could not find variable \"" +
                                     identifier->value + "\" in scope"
                              << std::endl;
                    exit(1);
                }
                compiled += asmFrontend.push(
                    "QWORD [rsp + " +
                    std::to_string((asmFrontend.stackSize - index - 1) * 8) +
                    "]");
            }
            void operator()(AST::StringLiteral*) {}
            void operator()(AST::Expression*) {}
        };

        TermVisitor visitor = {.compiled = compiled, .asmFrontend = *this};
        std::visit(visitor, term->var);

        return compiled;
    }
    int getVariableOffset(std::string variableName) {
        for (unsigned int i = 0; i < this->variableNames.size(); i++) {
            if (this->variableNames.at(i) == variableName)
                return i;
        }
        return -1;
    }
    void addVariable(std::string variableName) {
        this->variableNames.push_back(variableName);
    }
};
