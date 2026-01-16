#include "string.hpp"

std::vector<std::string> split(std::string& text, const std::string& delimiter) {
    std::vector<std::string> tokens;
    int startPos = 0;
    int endPos = 0;
    std::string token;
    while ((endPos = text.find(delimiter, startPos)) != std::string::npos) {
        tokens.push_back(text.substr(startPos, endPos - startPos));
        startPos = endPos + delimiter.length();
    }
    tokens.push_back(text.substr(startPos));

    return tokens;
}