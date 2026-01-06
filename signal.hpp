#pragma once
#include <functional>
#include <list>
#include <memory>

template<typename... Args>
class Signal {
public:
	void emit(Args... args) {
		for (auto it = subscribers.begin(); it != subscribers.end();) {
			auto& subscriber = *it;
			if (!subscriber->active) {
				it = subscribers.erase(it);
				continue;
			}

			subscriber->func(args...);
			it++;
		}
	}

	std::function<void()> subscribe(std::function<void(Args...)> func) {
		auto subscriber = std::make_shared<Slot>();
		subscriber->func = std::move(func);
		subscribers.push_back(subscriber);
		return [weak = std::weak_ptr<Slot>(subscriber)]() {
			if (auto s = weak.lock()) 
				s->active = false;
		};
	}

	int getListenerCount() { return static_cast<int>(subscribers.size()); }
private:
	struct Slot {
		std::function<void(Args...)> func;
		bool active = true;
	};

	std::list<std::shared_ptr<Slot>> subscribers = {};
};