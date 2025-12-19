#include "animatedSprite.hpp"

AnimatedSprite::AnimatedSprite(std::vector<Sprite>& sprites, float frameRate) : 
	sprites_(std::move(sprites)), 
	frameRate_(frameRate), 
	time_(0.0f), 
	currentFrame_(0), 
	maxFrames_(static_cast<unsigned int>(sprites_.size())) 
{}

AnimatedSprite::AnimatedSprite(std::shared_ptr<Tmpl8::Surface> surface, unsigned int frames, float frameRate, float scale)
	: sprites_({}), frameRate_(frameRate), time_(0.0f), currentFrame_(0), maxFrames_(frames) {
	sprites_.reserve(frames);

	int spriteWidth = surface->GetWidth() / frames;
	int spriteHeight = surface->GetHeight();
	int u = 0;
	int v = 0;

	for (unsigned int x = 0; x < frames; x++) {
		sprites_.emplace_back(Sprite(surface, Rect2<int>(u, v, spriteWidth, spriteHeight), scale));
		u += spriteWidth;
	}
}

AnimatedSprite::AnimatedSprite(AnimatedSprite& other, float frameRate, float scale) : 
	sprites_({}), 
	frameRate_(frameRate), 
	time_(0.0f), 
	currentFrame_(0), 
	maxFrames_(static_cast<unsigned int>(other.sprites_.size())) 
{
	sprites_.reserve(other.sprites_.size());
	for (unsigned int x = 0; x < other.sprites_.size(); x++) {
		sprites_.emplace_back(Sprite(other.sprites_[x], scale));
	}
}

void AnimatedSprite::process(float deltaTime) {
	time_ += deltaTime;
	if (time_ > duration()) time_ = 0.0f;
}

void AnimatedSprite::draw(Tmpl8::Surface* surface, float x, float y) {
	drawScaled(surface, x, y, 1.0f);
}

void AnimatedSprite::drawScaled(Tmpl8::Surface* surface, float x, float y, float scale) {
	setFrame(static_cast<unsigned int>(frameRate_ * time_));
	sprites_[currentFrame_].drawScaled(surface, x, y, scale);
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