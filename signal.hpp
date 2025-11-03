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

	std::function<void()> subscribe(std::function<void(Args...)> func) {
		auto it = subscribers.insert(subscribers.end(), func);
		return [this, it]() {
			subscribers.erase(it);
		};
	}
private:
	std::vector<std::function<void(Args...)>> subscribers;
};