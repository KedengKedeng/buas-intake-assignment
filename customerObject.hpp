#pragma once
#include "characterObject.hpp"
#include "customerType.hpp"
#include "subscriptionManager.hpp"
#include "item.hpp"

class CustomerObject : public CharacterObject, public SubscriptionManager {
public:
	CustomerObject(int64_t id, vec2<float> pos, std::shared_ptr<CustomerType> type, std::shared_ptr<Item> neededItem);

	void process(float deltaTime) override;

	void subscribe() override;
private:
	AnimatedSprite itemSprite;
	std::shared_ptr<Item> neededItem_;
};