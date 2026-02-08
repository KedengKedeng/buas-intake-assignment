#pragma once
#include "characterObject.hpp"
#include "customerType.hpp"
#include "subscriptionManager.hpp"
#include "item.hpp"
#include "wallet.hpp"
#include "inventory.hpp"

class CustomerObject : public CharacterObject, public SubscriptionManager {
public:
	CustomerObject(
		int64_t id, 
		vec2<float> pos, 
		std::shared_ptr<CustomerType> type, 
		std::shared_ptr<Item> neededItem,
		std::shared_ptr<Wallet> wallet,
		std::shared_ptr<Inventory> inventory
	);

	void process(float deltaTime) override;

	void subscribe() override;
private:
	std::shared_ptr<Wallet> wallet_;
	std::shared_ptr<Inventory> inventory_;

	AnimatedSprite itemSprite;
	std::shared_ptr<Item> neededItem_;
};