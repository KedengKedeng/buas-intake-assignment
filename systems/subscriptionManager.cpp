#include "subscriptionManager.hpp"

SubscriptionManager::~SubscriptionManager() {
	unsubscribe();
}

void SubscriptionManager::unsubscribe() {
	for (auto& unsubscriber : unsubscribers) unsubscriber();
	unsubscribers.clear();
}

void SubscriptionManager::addSubscription(std::function<void()> func) {
	unsubscribers.push_back(func);
}