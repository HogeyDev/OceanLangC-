#include "lexer.h"
#include "ocean.h"
#include "parser.h"
#include "token.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "No input file specified" << std::endl;
    std::cout << "\tusage: ocean path/to/example.ocn" << std::endl;
    exit(1);
  }

  std::string source = readFile(argv[1]);
  Lexer *lexer = new Lexer(source);
  Parser *parser = new Parser(lexer);
  parser->parse();
  return 0;
}
