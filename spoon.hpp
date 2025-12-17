#pragma once
#include "mouseMoveHandler.hpp"
#include "object.hpp"
#include "sprite.hpp"

extern Tmpl8::vec2 spoonVelocity;

class Spoon : public Object {
public:
	Spoon(int64_t id, Tmpl8::vec2& pos);

	void subscribe() override;
	void unsubscribe() override;

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
	void process(float deltaTime) override;
private:
	Tmpl8::vec2 velocity = spoonVelocity;

	MouseMoveHandler mouseMoveHandler;
	Sprite sprite_;
};