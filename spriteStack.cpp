#include "spriteStack.hpp"

void SpriteStack::draw(Tmpl8::Surface* surface, Tmpl8::vec2& pos) {
	unsigned int frames = sprites_[currentSprite_].getFrames();

	if (currentFrame_ > frames) currentFrame_ = 1;

	sprites_[currentSprite_].setFrame(static_cast<int>(currentFrame_));

	sprites_[currentSprite_].draw(surface, pos.x, pos.y);

	currentFrame_ += 0.1f;
};

void SpriteStack::drawNoAnimate(Tmpl8::Surface* surface, Tmpl8::vec2& pos) {
	sprites_[currentSprite_].draw(surface, pos.x, pos.y);
}