#include "spriteStack.hpp"

void SpriteStack::process(float deltaTime) {
	sprites_[currentSprite_].process(deltaTime);
}

void SpriteStack::draw(Tmpl8::Surface* surface, float x, float y) {
	sprites_[currentSprite_].draw(surface, x, y);
};