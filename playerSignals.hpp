#pragma once
#include <vector>
#include <functional>
#include "vector2.hpp"

class WalkSignal {
public:
	static void emit(Vector2 delta);
	static void subscribe(std::function<void(Vector2)> func) { subscribers.push_back(func); }
private:
	static std::vector<std::function<void(Vector2)>> subscribers;
};