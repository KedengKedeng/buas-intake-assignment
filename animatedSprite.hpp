#pragma once
#include "spritesheet.hpp"

class AnimatedSprite {
public:
	AnimatedSprite(std::shared_ptr<SpriteSheet> sheet, float frameRate, float scale = 1.0f);

	void process(float deltaTime);
	void draw(Tmpl8::Surface* surface, float x, float y);
	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale);

	void setFrameRate(float frameRate) { frameRate_ = frameRate; }
	float getFrameRate() const { return frameRate_; }

	const std::shared_ptr<SpriteSheet> getFrames() const { return sheet_; }

	float getWidth() const { return sheet_->getWidth() * scale_; }
	float getHeight() const { return sheet_->getHeight() * scale_; }

	float duration() const;

	void setFrame(unsigned int index);
private:
	const std::shared_ptr<SpriteSheet> sheet_;

	unsigned int currentFrame_;
	unsigned int maxFrames_;

	float scale_;

	float frameRate_;
	float time_;
};