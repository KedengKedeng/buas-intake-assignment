#pragma once
#include "surface.h"
#include "boundingBox.hpp"

class Object {
public:
	Object(Tmpl8::vec2 pos, BoundingBox& boundingBox) :
		pos_(pos), boundingBox_(boundingBox) { };

	void setPos(Tmpl8::vec2 pos) { pos_ = pos; }

	BoundingBox getBounds() { return boundingBox_; }
	BoundingBox getAbsoluteBounds() { return boundingBox_.at(pos_); }

	virtual void draw(Tmpl8::Surface* surface) = 0;
	virtual void process() = 0;
protected:
	Tmpl8::vec2 pos_;

	BoundingBox boundingBox_;
};