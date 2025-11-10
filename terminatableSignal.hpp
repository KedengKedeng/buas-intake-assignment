#pragma once
#include <functional>
#include <vector>
#include <forward_list>

template<typename... Args>
class TerminatableSignal {
public:
	void emit(Args... args) {
		bool terminate = false;
		for (auto& subscriber : subscribers) {
			if (terminate) return;
			terminate = subscriber(args...);
		}
	}

	std::function<void()> subscribe(std::function<bool(Args...)> func) {
		auto it = subscribers.insert(subscribers.end(), func);
		return [this, it]() {
			subscribers.erase(it);
			};
	}

	int getListenerCount() { return subscribers.size(); }
private:
	std::vector<std::function<bool(Args...)>> subscribers;
};