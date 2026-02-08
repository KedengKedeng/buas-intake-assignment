#pragma once
#include "object.hpp"
#include "item.hpp"
#include "interactable.hpp"
#include "subscriptionManager.hpp"

class ItemObject : public Object, public Interactable, public SubscriptionManager {
public:
	ItemObject(int64_t id, vec2<float> pos, std::shared_ptr<Item> item);

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	void process(float deltaTime) override;

	void subscribe() override;
private:
	const std::shared_ptr<Item> item_;
	mutable AnimatedSprite itemSprite;

	// TODO: randomize?
	float drawOffset = 0;
	float minDrawOffset = 0;
	float maxDrawOffset = 20;
	float drawOffsetStep = 0.5f;
};