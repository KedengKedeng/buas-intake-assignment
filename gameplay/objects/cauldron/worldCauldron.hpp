#pragma once
#include "object.hpp"
#include "spriteStack.hpp"
#include "cauldron.hpp"
#include "collider.hpp"
#include "interactable.hpp"
#include "subscriptionManager.hpp"

class WorldCauldron : public Object, public Collider, public Interactable, public SubscriptionManager {
public:
	WorldCauldron(int64_t id, vec2<float> pos, std::shared_ptr<Cauldron> cauldron);
	~WorldCauldron();

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
	void process(float deltaTime) override;

	void subscribe() override;
private:
	std::shared_ptr<Cauldron> cauldron_;

	std::function<void()> itemDroppedUnsub = []() {};

	void onInteractStart();
	void onInteractEnd();
	bool isInteracting = false;

	mutable SpriteStack sprites_;
};