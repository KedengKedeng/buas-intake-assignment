#pragma once
#include "template.h"
#include "signal.hpp"
#include "template.h"

class BoundingBox {
public:
	BoundingBox(Tmpl8::vec2 pos, Tmpl8::vec2 size): pos_(pos), size_(size) {};

	Signal<> onCollisionStart = Signal<>();
	Signal<> onCollisionEnd = Signal<>();

	Tmpl8::vec2 getPos() { return realWorldPos + pos_; }
	Tmpl8::vec2 getSize() { return size_; }
	void setPos(Tmpl8::vec2 pos) { realWorldPos = pos; }

	bool isInBounds(BoundingBox& box);
private:
	Tmpl8::vec2 realWorldPos;
	Tmpl8::vec2 pos_;
	Tmpl8::vec2 size_;
};