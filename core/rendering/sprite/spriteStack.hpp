#pragma once
#include "animatedSprite.hpp"
#include <vector>

class SpriteStack {
public:
	SpriteStack(const std::vector<AnimatedSprite>& sprites) : sprites_(sprites) {};

	void addSprite(AnimatedSprite& sprite) { sprites_.push_back(sprite); }
	void setSprite(int sprite) { currentSprite_ = sprite; }

	float getWidth() const { return sprites_[0].getWidth(); }
	float getHeight() const { return sprites_[0].getHeight(); }

	void process(float deltaTime);
	void draw(Tmpl8::Surface& surface, float x, float y) const;
private:
	int currentSprite_ = 0;
	mutable std::vector<AnimatedSprite> sprites_;
};