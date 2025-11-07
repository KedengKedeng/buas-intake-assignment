#pragma once
#include <random>

std::mt19937_64 mt(0);

int64_t getRandomNum() {
	return mt();
}