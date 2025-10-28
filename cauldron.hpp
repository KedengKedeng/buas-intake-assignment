#pragma once
#include "spriteObject.hpp"

class Cauldron : public SpriteObject {
public:
	Cauldron(Sprite& sprite, Tmpl8::vec2 pos) : 
		SpriteObject(
			pos, 
			BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(sprite.getWidth(), sprite.getHeight())), 
			ObservableBoundingBox(Tmpl8::vec2(-10), Tmpl8::vec2(sprite.getWidth() + 10, sprite.getHeight() + 10)),
			sprite
		) {}
	void process() override {}
};