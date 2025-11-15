#include "random.hpp"

std::mt19937_64 mt{ std::random_device{}() };

int64_t getRandomNum() {
    return static_cast<int64_t>(mt());
}