#pragma once
#include "spriteObject.hpp"

class Cauldron : public SpriteObject {
public:
	Cauldron(Sprite& sprite, Tmpl8::vec2 pos) : SpriteObject(pos, BoundingBox(Tmpl8::vec2(0, 0), Tmpl8::vec2(sprite.getWidth(), sprite.getHeight())), sprite) {}
	void process() override {}
};