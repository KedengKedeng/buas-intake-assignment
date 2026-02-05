#pragma once
#include "object.hpp"
#include "mouseHandler.hpp"
#include "interactable.hpp"
#include "spritesheet.hpp"
#include "vec2.hpp"
#include "subscriptionManager.hpp"

class Blower : public Object, public Interactable, public SubscriptionManager {
public:
	Blower(int64_t id, vec2<float> pos);

	void addBlowerPosition(float delta);

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	void process(float deltaTime) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	bool inflate = true;
	float blowerPosition = 0;
	MouseHandler mouseHandler_;
	const std::shared_ptr<SpriteSheet> sprites_;
};