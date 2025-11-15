#include "spriteObject.hpp"

void SpriteObject::draw(Tmpl8::Surface* surface) {
	unsigned int frames = sprites_[currentSprite_].getFrames();

	if (currentFrame_ > frames) currentFrame_ = 1;

	sprites_[currentSprite_].setFrame(static_cast<int>(currentFrame_));

	sprites_[currentSprite_].draw(surface, pos_.x, pos_.y);

	currentFrame_ += 0.1f;
};