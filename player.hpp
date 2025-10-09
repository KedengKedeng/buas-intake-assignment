#pragma once
#include "object.hpp"
#include "playerSignals.hpp"

struct Velocity {
	int x;
	int y;
};

class Player: public Object {
public:
	Player(Tmpl8::Sprite& sprite, int x, int y): Object(sprite, x, y) {
		WalkSignal::subscribe([this](int x, int y) { 
			addVelocityX(x); 
			addVelocityY(y);
		});
	};

	void move();
	void addVelocityX(int x) { velocity.x += x; }
	void addVelocityY(int y) { velocity.y += y; }

	void process() override;
private:
	Velocity velocity = {0, 0};
};