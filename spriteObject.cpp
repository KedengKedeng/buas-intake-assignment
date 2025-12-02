#include "spriteObject.hpp"

void SpriteObject::draw(Tmpl8::Surface* surface) {
	SpriteStack::draw(surface, pos_);
};