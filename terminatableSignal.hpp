#pragma once
#include <functional>
#include <list>
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

			// See signal.hpp for explenation.
			return emptyFunc;
		};
	}

	int getListenerCount() { return subscribers.size(); }
private:
	std::list<std::function<bool(Args...)>> subscribers;
};