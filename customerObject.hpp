#pragma once
#include "characterObject.hpp"
#include "customerType.hpp"
#include "subscriptionManager.hpp"
#include "item.hpp"
#include "wallet.hpp"
#include "inventory.hpp"
#include "itemLog.hpp"

class CustomerObject : public CharacterObject, public SubscriptionManager {
public:
	CustomerObject(
		int64_t id, 
		vec2<float> pos, 
		std::shared_ptr<CustomerType> type, 
		std::shared_ptr<Wallet> wallet,
		std::shared_ptr<Inventory>,
		std::shared_ptr<ItemLog> itemLog
	);

	std::shared_ptr<Item> getRandomItem() const;

	void process(float deltaTime) override;

	void subscribe() override;
private:
	std::shared_ptr<Wallet> wallet_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<ItemLog> itemLog_;

	std::shared_ptr<Item> neededItem_;
	AnimatedSprite itemSprite;
};