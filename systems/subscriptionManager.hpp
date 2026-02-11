#pragma once
#include <vector>
#include <functional>

class SubscriptionManager {
public:
	virtual ~SubscriptionManager();

	virtual void subscribe() {};
	virtual void unsubscribe();

	void addSubscription(std::function<void()> sub);
private:
	std::vector<std::function<void()>> unsubscribers = {};
};