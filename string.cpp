#include "string.hpp"

std::vector<std::string> split(const std::string& text, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t startPos = 0;
    size_t endPos = 0;
    std::string token;
    while ((endPos = text.find(delimiter, startPos)) != std::string::npos) {
        tokens.push_back(text.substr(startPos, endPos - startPos));
        startPos = endPos + delimiter.length();
    }
    tokens.push_back(text.substr(startPos));

    return tokens;
}