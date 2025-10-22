#pragma once
#include "spriteObject.hpp"
#include "playerSignals.hpp"
#include "template.h"
#include <cstdio>

class Player : public SpriteObject {
public:
	Player(Tmpl8::Sprite& sprite, Tmpl8::vec2 pos) :
		SpriteObject(pos, BoundingBox(Tmpl8::vec2(0, 0), Tmpl8::vec2(sprite.GetWidth(), sprite.GetHeight())), sprite) {
		walkSignal.subscribe([this](Tmpl8::vec2& delta) {
			addDelta(delta);
		});
	};

	void move(Tmpl8::vec2 newPos);
	void calculateMove();

	void addDelta(Tmpl8::vec2 delta) { delta_ += delta; }

	void process() override;
private:
	Tmpl8::vec2 velocity = { 10, 10 };
	Tmpl8::vec2 delta_ = { 0, 0 };
};