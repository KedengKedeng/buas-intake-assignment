#pragma once
#include "object.hpp"
#include "playerSignals.hpp"
#include "template.h"
#include <cstdio>

class Player : public Object {
public:
	Player(Tmpl8::Sprite& sprite, int x, int y) :
		Object(x, y, BoundingBox(Tmpl8::vec2(0, 0), Tmpl8::vec2(sprite.GetWidth(), sprite.GetHeight()))), sprite_(sprite) {
		walkSignal.subscribe([this](Tmpl8::vec2 delta) {
			addDeltaX(delta.x);
			addDeltaY(delta.y);
		});
	};


	void move(Tmpl8::vec2 newPos);
	void calculateMove();

	void addDeltaX(float x) { delta_.x += x; }
	void addDeltaY(float y) { delta_.y += y; }

	void draw(Tmpl8::Surface* surface) override;
	void process() override;
private:
	Tmpl8::Sprite sprite_;
	Tmpl8::vec2 velocity = { 10, 10 };
	Tmpl8::vec2 delta_ = { 0, 0 };
};