#pragma once
#include "object.hpp"
#include "playerSignals.hpp"
#include "template.h"

class Player: public Object {
public:
	Player(Tmpl8::Sprite& sprite, int x, int y): Object(sprite, x, y) {
		walkSignal.subscribe([this](Tmpl8::vec2 delta) {
			addDeltaX(delta.x); 
			addDeltaY(delta.y);
		});
	};

	void move();
	void addDeltaX(int x) { delta.x += x; }
	void addDeltaY(int y) { delta.y += y; }

	void process() override;
private:
	Tmpl8::vec2 velocity = {10, 10};
	Tmpl8::vec2 delta = { 0, 0 };
};