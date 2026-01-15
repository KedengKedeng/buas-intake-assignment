#pragma once
#include "boundingBox.hpp"
#include "signal.hpp"

class Collider {
public:
	Collider() : collidingBox_() {}
	Collider(const vec2<float>& pos, const vec2<float>& size): collidingBox_(pos, size) {}

	BoundingBox getColliderBounds() { return collidingBox_; }
	BoundingBox getColliderBoundsAt(vec2<float>& pos) { return collidingBox_.at(pos); }

	vec2<float> getColliderPos() { return collidingBox_.getPos(); }
	vec2<float> getColliderSize() { return collidingBox_.getSize(); }

	Signal<> onCollisionStart{};
	Signal<> onCollisionEnd{};
protected:
	BoundingBox collidingBox_;
};