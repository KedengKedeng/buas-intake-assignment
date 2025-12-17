#include "animatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const Sprite& sprite, float frameRate) 
	: sprite_(std::move(sprite)), frameRate_(frameRate), time_(0.0f){}

void AnimatedSprite::process(float deltaTime) {
	time_ += deltaTime;
	if (time_ > duration()) time_ = 0.0f;
}

void AnimatedSprite::draw(Tmpl8::Surface* surface, float x, float y) {
	drawScaled(surface, x, y, 1.0f);
}

void AnimatedSprite::drawScaled(Tmpl8::Surface* surface, float x, float y, float scale) {
	sprite_.setFrame(static_cast<unsigned int>(frameRate_ * time_));
	sprite_.drawScaled(surface, x, y, scale);
}

float AnimatedSprite::duration() {
	return sprite_.getFrames() / frameRate_;
}