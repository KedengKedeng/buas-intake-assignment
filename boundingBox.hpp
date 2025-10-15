#pragma once
#include "template.h"
#include "signal.hpp"

class BoundingBox {
public:
	BoundingBox(Tmpl8::vec2 pos, Tmpl8::vec2 size): pos_(pos), size_(size) {};

	Signal<> onCollisionStart = Signal<>();
	Signal<> onCollisionEnd = Signal<>();

	Tmpl8::vec2 getPos() { return pos_; }
	Tmpl8::vec2 getSize() { return size_; }

	BoundingBox at(Tmpl8::vec2 pos) { return BoundingBox(pos + pos_, size_); }

	bool isInBounds(BoundingBox& box);
private:
	Tmpl8::vec2 pos_;
	Tmpl8::vec2 size_;
};