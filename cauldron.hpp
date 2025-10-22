#pragma once
#include "spriteObject.hpp"

static Tmpl8::Sprite cauldronSprite(new Tmpl8::Surface("assets/turret.tga"), 24);

class Cauldron : public SpriteObject {
public:
	Cauldron(Tmpl8::vec2 pos) : SpriteObject(pos, BoundingBox(Tmpl8::vec2(0, 0), Tmpl8::vec2(cauldronSprite.GetWidth(), cauldronSprite.GetHeight())), cauldronSprite) {}
	void process() override {}
};