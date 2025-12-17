#pragma once
#include "object.hpp"
#include "sprite.hpp"
#include "spriteStack.hpp"
#include <vector>

class SpriteObject : public Object, public SpriteStack {
public:
	SpriteObject(int64_t id, Tmpl8::vec2& pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox):
		Object(id, pos, boundingBox, interactionBoundingBox), SpriteStack({}) {
	}
	
	virtual void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
	virtual void process(float deltaTime) override;
};