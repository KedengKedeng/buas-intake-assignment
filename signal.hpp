#pragma once
#include <functional>
#include <vector>
#include <forward_list>

template<typename... Args>
class Signal {
public:
	void emit(Args... args) {
		for (auto& subscriber : subscribers)
			subscriber(args...);
	}
	void subscribe(std::function<void(Args...)> func) {
		subscribers.push_back(func);
	}
private:
	std::vector<std::function<void(Args...)>> subscribers;
};