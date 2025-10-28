#pragma once
#include "object.hpp"
#include "sprite.hpp"

class SpriteObject : public Object {
public:
	SpriteObject(Tmpl8::vec2 pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox, Sprite& sprite):
		Object(pos, boundingBox, interactionBoundingBox), sprite_(sprite) {}
	
	virtual void draw(Tmpl8::Surface* surface) override { sprite_.draw(surface, static_cast<int>(pos_.x), static_cast<int>(pos_.y)); };
	virtual void process() = 0;
protected:
	Sprite sprite_;
};