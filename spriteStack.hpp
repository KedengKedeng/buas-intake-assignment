#pragma once
#include "animatedSprite.hpp"
#include "template.h"
#include <vector>

class SpriteStack {
public:
	SpriteStack(const std::vector<AnimatedSprite>& sprites) : sprites_(std::move(sprites)) {};

	void addSprite(AnimatedSprite& sprite) { sprites_.push_back(sprite); }
	void setSprite(int sprite) { currentSprite_ = sprite; }

	float getWidth() { return sprites_[0].getWidth(); }
	float getHeight() { return sprites_[0].getHeight(); }

	void process(float deltaTime);
	void draw(Tmpl8::Surface* surface, float x, float y);
private:
	int currentSprite_ = 0;
	std::vector<AnimatedSprite> sprites_;
};