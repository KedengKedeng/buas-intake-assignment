#pragma once
#include "boundingBox.hpp"
#include "signal.hpp"
#include "rect2.hpp"
#include "surface.h"

class Collider {
public:
	Collider() : collidingBoxes_({}) {}
	Collider(vec2<float> pos, vec2<float> size) : collidingBoxes_({ BoundingBox(pos, size) }) {}
	Collider(const std::vector<BoundingBox>& boxes) : collidingBoxes_(boxes) {}

	const std::vector<BoundingBox>& getColliderBounds() const { return collidingBoxes_; }

	Rect2<float> getColliderPos() const;
	Rect2<float> getColliderSize() const;
	void addCollider(const BoundingBox& box);

	vec2<float> swept(Collider& other, vec2<float> velocity, vec2<float> at, vec2<float> otherAt) const;

	std::vector<BoundingBox>::iterator begin() { return collidingBoxes_.begin(); }
	std::vector<BoundingBox>::iterator end() { return collidingBoxes_.end(); }

	// debug function
	void drawColliders(Tmpl8::Surface* surface, const vec2<float>& offset);

	Signal<> onCollisionStart{};
	Signal<> onCollisionEnd{};
private:
	std::vector<BoundingBox> collidingBoxes_;
};