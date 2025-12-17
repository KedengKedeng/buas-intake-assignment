#include "spriteObject.hpp"

void SpriteObject::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	SpriteStack::draw(surface, pos_.x + offset.x, pos_.y + offset.y);
};

void SpriteObject::process(float deltaTime) {
	SpriteStack::process(deltaTime);
}