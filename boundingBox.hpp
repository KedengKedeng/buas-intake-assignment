#pragma once
#include "template.h"
#include "signal.hpp"

struct CollisionResult {
	float normalX;
	float normalY;
	float time;
	bool collision;
};

struct SweptAxisResult {
	Tmpl8::vec2 timings;
	bool collision;
};

class BoundingBox {
public:
	BoundingBox() : pos_(Tmpl8::vec2(0)), size_(Tmpl8::vec2(0)) {}
	BoundingBox(const Tmpl8::vec2& pos, const Tmpl8::vec2& size): pos_(pos), size_(size) {};

	Tmpl8::vec2 getPos() { return pos_; }
	void setPos(Tmpl8::vec2& pos) { pos_ = pos; }
	Tmpl8::vec2 getSize() { return size_; }
	void setSize(Tmpl8::vec2& size) { size_ = size; }

	// return a version of the bounding box with the given position added.
	// mainly used to compared bounding boxes on a plane.
	BoundingBox at(Tmpl8::vec2& pos) { return BoundingBox(pos + pos_, size_); }

	virtual bool isInBounds(BoundingBox& box);
	virtual CollisionResult swept(BoundingBox& box, Tmpl8::vec2& velocity);
protected:
	SweptAxisResult BoundingBox::getSweptTimings(float firstPos, float secondPos, float firstSize, float secondSize, float velocity);

	Tmpl8::vec2 pos_;
	Tmpl8::vec2 size_;
};