#pragma once
#include "characterObject.hpp"
#include "subscriptionManager.hpp"

class Player : public CharacterObject, public SubscriptionManager {
public:
	Player(int64_t id, vec2<float>& pos);

	void subscribe() override;
};