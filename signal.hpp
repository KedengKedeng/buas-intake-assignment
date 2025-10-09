#pragma once
#include <functional>
#include <vector>

template<typename... Args>
class Signal {
public:
	void emit(Args&... args) {
		for (auto& subscriber : subscribers)
			// This line gives me an error about forgetting a )
			// but nothing seems to be missing and the program compiles?
			subscriber(args...);
	}
	void subscribe(std::function<void(Args...)> func) { subscribers.push_back(func); }
private:
	std::vector<std::function<void(Args...)>> subscribers = {};
};