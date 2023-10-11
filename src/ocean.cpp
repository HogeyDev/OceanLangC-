#include "ocean.hpp"
#include <fstream>
#include <string>
#include "parser.hpp"
#include "lexer.hpp"
#include "asm.hpp"
#include "debug.hpp"

std::string readFile(std::string filePath) {
    std::ifstream file(filePath);
    std::string contents;
    std::string line;
    while (getline(file, line)) {
        contents.append(line);
        contents.push_back('\n');
    }
    file.close();
    return contents;
}

void writeFile(std::string filePath, std::string contents) {
    std::ofstream file(filePath);
    file << contents;
    file.close();
}

std::string oceanCompile(std::string filePath) {
	// read file
	std::string source = readFile(filePath);
    // get tokens
	Lexer* lexer = new Lexer(source);
    std::vector<Token*> tokenList = lexer->getTokenList();
    for (auto& t : tokenList)
        std::cout << getPrintableToken(t) << std::endl;
    std::cout << std::endl;
    // parse into AST
	Parser* parser = new Parser(tokenList);
    AST::Program* program = parser->parse();
    std::cout << DEBUG::getPrintableProgram(program) << std::endl;
	// compile into asm
	AsmFrontend* asmFrontend = new AsmFrontend(program);
	std::string compiledCode = asmFrontend->compile();

	return compiledCode;
}