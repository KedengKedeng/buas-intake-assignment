#pragma once
#include "vec2.hpp"

struct CollisionResult {
	float time;
	int8_t normalX;
	int8_t normalY;
	bool collision;
};

struct SweptAxisResult {
	vec2<float> timings;
	bool collision;
};

class BoundingBox {
public:
	BoundingBox() : pos_(vec2<float>(0.0f)), size_(vec2<float>(0.0f)) {}
	BoundingBox(const vec2<float>& pos, const vec2<float>& size): pos_(pos), size_(size) {};

	vec2<float> getPos() { return pos_; }
	void setPos(vec2<float>& pos) { pos_ = pos; }
	vec2<float> getSize() { return size_; }
	void setSize(vec2<float>& size) { size_ = size; }

	// return a version of the bounding box with the given position added.
	// mainly used to compared bounding boxes on a plane.
	BoundingBox at(vec2<float>& pos) { return BoundingBox(pos + pos_, size_); }

	bool isInBounds(BoundingBox& box);
	bool isInBounds(vec2<float>& point);
	CollisionResult swept(BoundingBox& box, vec2<float>& velocity);
private:
	SweptAxisResult BoundingBox::getSweptTimings(float firstPos, float secondPos, float firstSize, float secondSize, float velocity);

	vec2<float> pos_, size_;
};