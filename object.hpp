#pragma once
#include "surface.h"

class Object {
public:
	Object(Tmpl8::Sprite& sprite, int x, int y): sprite_(sprite), x_(x), y_(y) {};

	void draw(Tmpl8::Surface* surface) { sprite_.Draw(surface, x_, y_); }
	void setX(int x) { x_ = x; }
	void setY(int y) { y_ = y; }

	virtual void process() = 0;
protected:
	Tmpl8::Sprite sprite_;

	int x_;
	int y_;
};