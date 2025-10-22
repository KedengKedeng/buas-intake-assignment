#pragma once
#include "object.hpp"

class SpriteObject : public Object {
public:
	SpriteObject(Tmpl8::vec2 pos, BoundingBox& boundingBox, Tmpl8::Sprite& sprite): 
		Object(pos, boundingBox), sprite_(sprite) {}
	
	virtual void draw(Tmpl8::Surface* surface) override { sprite_.Draw(surface, pos_.x, pos_.y); };
	virtual void process() = 0;
protected:
	Tmpl8::Sprite sprite_;
};