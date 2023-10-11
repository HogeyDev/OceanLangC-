#pragma once

#include <fstream>
#include <string>

std::string readFile(std::string filePath);
void writeFile(std::string filePath, std::string contents);
std::string oceanCompile(std::string filePath);