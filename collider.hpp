#pragma once
#include "boundingBox.hpp"
#include "signal.hpp"
#include "rect2.hpp"

class Collider {
public:
	Collider() : collidingBoxes_({}) {}
	Collider(const vec2<float>& pos, const vec2<float>& size) : collidingBoxes_({ BoundingBox(pos, size) }) {}
	Collider(const std::vector<BoundingBox>& boxes) : collidingBoxes_(std::move(boxes)) {}

	std::vector<BoundingBox>& getColliderBounds() { return collidingBoxes_; }

	Rect2<float> getColliderPos();
	Rect2<float> getColliderSize();

	CollisionResult swept(Collider& other, vec2<float>& velocity, vec2<float>& at, vec2<float>& otherAt);

	std::vector<BoundingBox>::iterator begin() { return collidingBoxes_.begin(); }
	std::vector<BoundingBox>::iterator end() { return collidingBoxes_.end(); }

	Signal<> onCollisionStart{};
	Signal<> onCollisionEnd{};
protected:
	std::vector<BoundingBox> collidingBoxes_;
};