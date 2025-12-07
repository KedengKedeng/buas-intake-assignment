#pragma once
#include "mouseMoveHandler.hpp"
#include "spriteObject.hpp"

extern Tmpl8::vec2 spoonVelocity;

class Spoon : public SpriteObject {
public:
	Spoon(int64_t id, Tmpl8::vec2& pos);

	void subscribe() override;
	void unsubscribe() override;

	void process() override;
private:
	Tmpl8::vec2 velocity = spoonVelocity;

	MouseMoveHandler mouseMoveHandler;
};