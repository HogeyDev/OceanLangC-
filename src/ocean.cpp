#include "ocean.h"
#include <fstream>
#include <string>

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
