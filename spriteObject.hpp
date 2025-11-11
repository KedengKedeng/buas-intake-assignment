#pragma once
#include "object.hpp"
#include "sprite.hpp"
#include <vector>

class SpriteObject : public Object {
public:
	SpriteObject(int64_t id, Tmpl8::vec2 pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox):
		Object(id, pos, boundingBox, interactionBoundingBox) {}
	
	virtual void draw(Tmpl8::Surface* surface) override {
		unsigned int frames = sprites_[currentSprite_].getFrames();

		if (currentFrame_ > frames) currentFrame_ = 1;

		sprites_[currentSprite_].setFrame(static_cast<int>(currentFrame_));

		sprites_[currentSprite_].draw(surface, static_cast<int>(pos_.x), static_cast<int>(pos_.y)); 

		currentFrame_+=0.1f;
	};
protected:
	float currentFrame_ = 1;
	int currentSprite_ = 0;
	std::vector<Sprite> sprites_ = {};
};