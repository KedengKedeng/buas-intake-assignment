#pragma once
#include "object.hpp"
#include "playerSignals.hpp"
#include "vector2.hpp"

class Player: public Object {
public:
	Player(Tmpl8::Sprite& sprite, int x, int y): Object(sprite, x, y) {
		WalkSignal::subscribe([this](Vector2 delta) { 
			addDeltaX(delta.x); 
			addDeltaY(delta.y);
		});
	};

	void move();
	void addDeltaX(int x) { delta.x += x; }
	void addDeltaY(int y) { delta.y += y; }

	void process() override;
private:
	Vector2 velocity = {10, 10};
	Vector2 delta = { 0, 0 };
};