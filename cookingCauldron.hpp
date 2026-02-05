#pragma once
#include "cauldron.hpp"
#include "object.hpp"
#include "animatedSprite.hpp"
#include "interactable.hpp"
#include "collider.hpp"
#include "subscriptionManager.hpp"

class CookingCauldron : public Object, public Interactable, public Collider, public SubscriptionManager {
public:
	CookingCauldron(int64_t id, std::shared_ptr<Cauldron> cauldron);

	void drawBack(Tmpl8::Surface* surface, vec2<float> offset) const;
	void drawFront(Tmpl8::Surface* surface, vec2<float> offset) const;
	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override {};
	void process(float deltaTime) override;

	void subscribe() override;
private:
	std::shared_ptr<Cauldron> cauldron_;
	const Sprite cauldronFront;
	const Sprite cauldronBack;
	mutable AnimatedSprite cauldronInside;
	mutable AnimatedSprite fire;
};