#include "asm.hpp"
#include "ast.hpp"
#include "debug.hpp"
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
    // compile file
    std::string compiledCode = oceanCompile(argv[1]);

    // create binary
    writeFile("example/main.asm", compiledCode);
    int res = system("nasm -f elf64 example/main.asm -o example/main.o");
    res = system("ld -m elf_x86_64 example/main.o -o example/main.out");
    res = system("rm example/main.o");
    if (!outputAssemblyFile)
        res = system("rm example/main.asm");
    (void)res;

    return 0;
}
