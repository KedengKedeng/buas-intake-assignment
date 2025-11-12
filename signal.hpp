#pragma once
#include <functional>
#include <vector>
#include <forward_list>
#include <memory>

template<typename... Args>
class Signal {
public:
	void emit(Args... args) {
		for (auto& subscriber : subscribers)
			subscriber(args...);
	}

	std::function<void()> subscribe(std::function<void(Args...)> func) {
		std::shared_ptr<bool> valid = std::make_shared<bool>(true);
		auto it = subscribers.insert(subscribers.end(), func);
		return [this, it, valid]() {
			if (!*valid) return;
			*valid = false;
			subscribers.erase(it);
		};
	}

	int getListenerCount() { return static_cast<int>(subscribers.size()); }
private:
	std::vector<std::function<void(Args...)>> subscribers;
};