#pragma once
#include "sprite.hpp"
#include "template.h"
#include <vector>

class SpriteStack {
public:
	SpriteStack(std::vector<Sprite>& sprites) : sprites_(sprites) {};

	void addSprite(Sprite& sprite) { sprites_.push_back(sprite); }
	void setSprite(int sprite) { currentSprite_ = sprite; }

	float getWidth() { return sprites_[0].getWidth(); }
	float getHeight() { return sprites_[0].getHeight(); }

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& pos);
private:
	float currentFrame_ = 1;
	int currentSprite_ = 0;
	std::vector<Sprite> sprites_;
};