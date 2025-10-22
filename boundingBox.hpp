#pragma once
#include "template.h"
#include "signal.hpp"

struct CollisionResult {
	bool collision;      // True if collision occurs
	float normalX;       // Collision normal X (-1, 0, or 1)
	float normalY;       // Collision normal Y (-1, 0, or 1)
	float time;          // Time of collision (0 to 1)
};

struct SweptAxisResult {
	bool collision;
	Tmpl8::vec2 timings;
};

class BoundingBox {
public:
	BoundingBox(Tmpl8::vec2 pos, Tmpl8::vec2 size): pos_(pos), size_(size) {};

	Tmpl8::vec2 getPos() { return pos_; }
	Tmpl8::vec2 getSize() { return size_; }

	BoundingBox at(Tmpl8::vec2 pos) { return BoundingBox(pos + pos_, size_); }

	bool isInBounds(BoundingBox& box);
	CollisionResult swept(BoundingBox& box, Tmpl8::vec2 velocity);
private:
	SweptAxisResult BoundingBox::getSweptTimings(float firstPos, float secondPos, float firstSize, float secondSize, float velocity);

	Tmpl8::vec2 pos_;
	Tmpl8::vec2 size_;
};