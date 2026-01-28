#pragma once
#include "spritesheet.hpp"

class AnimatedSprite {
public:
	AnimatedSprite(std::shared_ptr<SpriteSheet> sheet, float frameRate, float scale = 1.0f);

	void process(float deltaTime);
	void draw(Tmpl8::Surface* surface, float x, float y);
	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale);

	void setFrameRate(float frameRate) { frameRate_ = frameRate; }
	float getFrameRate() { return frameRate_; }

	std::shared_ptr<SpriteSheet> getFrames() { return sheet_; }

	float getWidth() { return sheet_->getWidth() * scale_; }
	float getHeight() { return sheet_->getHeight() * scale_; }

	float duration();

	void setFrame(unsigned int index);
private:
	std::shared_ptr<SpriteSheet> sheet_;

	unsigned int currentFrame_;
	unsigned int maxFrames_;

	float scale_;

	float frameRate_;
	float time_;
};