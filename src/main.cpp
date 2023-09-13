#include "lexer.h"
#include "ocean.h"
#include "token.h"
#include <iostream>
#include <vector>

int main() {
    std::string source = readFile("example/main.ocn");
    Lexer *lexer = new Lexer(source);
    Token *currentToken;
    while ((currentToken = lexer->nextToken())->type != TokenType::ENDOFFILE) {
        std::cout << getPrintableToken(currentToken) << std::endl;
        break;
    }
    return 0;
}
