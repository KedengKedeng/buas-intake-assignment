#pragma once
#include <vector>
#include <functional>

class WalkSignal {
public:
	static void emit(int x, int y);
	static void subscribe(std::function<void(int, int)> func) { subscribers.push_back(func); }
private:
	static std::vector<std::function<void(int, int)>> subscribers;
};