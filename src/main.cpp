#include "lexer.hpp"
#include "ocean.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No input file specified" << std::endl;
        std::cerr << "\tusage: ocean path/to/example.ocn" << std::endl;
        exit(1);
    }

    std::string source = readFile(argv[1]);
    Lexer* lexer = new Lexer(source);
    std::vector<Token*> tokenList = lexer->getTokenList();
    for (auto& t : tokenList)
        std::cout << getPrintableToken(t) << std::endl;
    std::cout << std::endl;
    Parser* parser = new Parser(tokenList);
    parser->parse();

    return 0;
}
