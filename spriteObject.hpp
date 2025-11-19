#pragma once
#include "object.hpp"
#include "sprite.hpp"
#include <vector>

class SpriteObject : public Object {
public:
	SpriteObject(int64_t id, Tmpl8::vec2& pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox):
		Object(id, pos, boundingBox, interactionBoundingBox) {}
	
	virtual void draw(Tmpl8::Surface* surface) override;
protected:
	float currentFrame_ = 1;
	int currentSprite_ = 0;
	std::vector<Sprite> sprites_ = {};
};