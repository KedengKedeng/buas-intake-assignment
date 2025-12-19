#pragma once
#include "sprite.hpp"
#include "template.h"
#include <vector>

class AnimatedSprite {
public:
	AnimatedSprite(std::vector<Sprite>& sprites, float frameRate);
	AnimatedSprite(std::shared_ptr<Tmpl8::Surface> surface, unsigned int frames, float frameRate, float scale = 1.0f);
	AnimatedSprite(AnimatedSprite& other, float frameRate, float scale = 1.0f);

	void process(float deltaTime);
	void draw(Tmpl8::Surface* surface, float x, float y);
	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale);

	void setFrameRate(float frameRate) { frameRate_ = frameRate; }
	float getFrameRate() { return frameRate_; }

	std::vector<Sprite>& getFrames() { return sprites_; }

	float getWidth() { return sprites_.at(0).getWidth(); }
	float getHeight() { return sprites_.at(0).getHeight(); }

	float duration();

	void setFrame(unsigned int index);
private:
	std::vector<Sprite> sprites_;

	unsigned int currentFrame_;
	unsigned int maxFrames_;

	float frameRate_;
	float time_;
};