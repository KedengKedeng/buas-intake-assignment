#pragma once
#include <vector>
#include <functional>

class WalkLeftSignal {
public:
	static void emit(int x);
	static void subscribe(std::function<void(int)> func) { subscribers.push_back(func); }
private:
	static std::vector<std::function<void(int)>> subscribers;
};