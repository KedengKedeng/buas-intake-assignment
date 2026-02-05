#pragma once
#include "mouseHandler.hpp"
#include "object.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include "interactable.hpp"
#include "subscriptionManager.hpp"

extern vec2<float> spoonVelocity;

class Spoon : public Object, public Collider, public Interactable, public SubscriptionManager {
public:
	Spoon(int64_t id, vec2<float> pos);

	void subscribe() override;
	void unsubscribe() override;

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	void process(float deltaTime) override;
private:
	vec2<float> velocity = spoonVelocity;

	MouseHandler mouseHandler;
	const Sprite sprite_;
};