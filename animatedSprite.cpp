#include "animatedSprite.hpp"

AnimatedSprite::AnimatedSprite(std::shared_ptr<SpriteSheet> sheet, float frameRate, float scale) : 
	sheet_(sheet),
	frameRate_(frameRate), 
	time_(0.0f), 
	currentFrame_(0), 
	maxFrames_(static_cast<unsigned int>(sheet->getSpriteCount())),
	scale_(scale)
{}

void AnimatedSprite::process(float deltaTime) {
	time_ += deltaTime;
	if (time_ > duration()) time_ = 0.0f;
}

void AnimatedSprite::draw(Tmpl8::Surface* surface, float x, float y) {
	drawScaled(surface, x, y, 1.0f);
}

void AnimatedSprite::drawScaled(Tmpl8::Surface* surface, float x, float y, float scale) {
	setFrame(static_cast<unsigned int>(frameRate_ * time_));
	Sprite& currentSprite = sheet_->getSprite(currentFrame_);
	currentSprite.drawScaled(surface, x, y, scale * scale_);
}

float AnimatedSprite::duration() {
	return maxFrames_ / frameRate_;
}

void AnimatedSprite::setFrame(unsigned int index) {
	// clamp index to existing frames
	index = std::min(index, maxFrames_);
	index = std::max(index, unsigned int(0));

	currentFrame_ = index;
}