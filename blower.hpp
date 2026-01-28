#pragma once
#include "object.hpp"
#include "mouseMoveHandler.hpp"
#include "interactable.hpp"
#include "spritesheet.hpp"
#include "vec2.hpp"
#include "subscriptionManager.hpp"

class Blower : public Object, public Interactable, public SubscriptionManager {
public:
	Blower(int64_t id, vec2<float>& pos);

	void addBlowerPosition(float delta);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	void process(float deltaTime) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	bool inflate = true;
	float blowerPosition = 0;
	MouseMoveHandler mouseMoveHandler;
	std::shared_ptr<SpriteSheet> sprites_;
};