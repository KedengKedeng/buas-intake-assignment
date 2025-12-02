#pragma once
#include "mouseMoveHandler.hpp"
#include "spriteObject.hpp"

class Spoon : public SpriteObject {
public:
	Spoon(int64_t id, Tmpl8::vec2& pos);

	void subscribe() override;
	void unsubscribe() override;
private:
	MouseMoveHandler mouseMoveHandler;
};