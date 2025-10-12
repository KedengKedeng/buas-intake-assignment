#pragma once
#include "surface.h"
#include "boundingBox.hpp"

class Object {
public:
	Object(int x, int y, BoundingBox& boundingBox): 
		x_(x), y_(y), boundingBox_(boundingBox) {boundingBox_.setPos(Tmpl8::vec2(x_, y_));};

	void setX(int x) { x_ = x; }
	void setY(int y) { y_ = y; }
	BoundingBox getBounds() { return boundingBox_; }

	virtual void draw(Tmpl8::Surface* surface) = 0;
	virtual void process() = 0;
protected:
	int x_;
	int y_;

	BoundingBox boundingBox_;
};