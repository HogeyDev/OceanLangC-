#include "include/lexer.h"
#include "include/ocean.h"
#include "include/token.h"
#include <iostream>
#include <vector>

int main() {
    std::string source = readFile("example/main.ocn");
    Lexer *lexer = new Lexer(source);
    Token *currentToken = nullptr;
    while ((currentToken = lexer->nextToken())->type != TokenType::ENDOFFILE) {
    	// std::cout << getPrintableToken(currentToken) << std::endl;
	}
    return 0;
}