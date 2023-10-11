#pragma once

#include "ast.hpp"
#include "ocean.hpp"
#include <string>

class AsmFrontend {
  public:
	AST::Program* root;
	AsmFrontend(AST::Program* root) {
		this->root = root;
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
		struct StatementVisitor {
			std::string& assembly;
			void operator()(AST::VariableAssignment* variableAssignment) {
				// TODO
				exit(2);
			}
			void operator()(AST::FunctionDeclaration* functionDeclaration) {
				// TODO
				exit(2);
			}
			void operator()(AST::FunctionCall* functionCall) {
				// TODO
				exit(2);
			}
			void operator()(AST::Import* importStatement) {
				assembly += oceanCompile(importStatement->filePath);
			}
		};
	}
};