#include "spriteObject.hpp"

void SpriteObject::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	SpriteStack::draw(surface, pos_ + offset);
};