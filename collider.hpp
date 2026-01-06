#pragma once
#include "boundingBox.hpp"

class Collider {
public:
	Collider() : collidingBox_() {}
	Collider(const Tmpl8::vec2& pos, const Tmpl8::vec2& size): collidingBox_(pos, size) {}

	BoundingBox getColliderBounds() { return collidingBox_; }
	BoundingBox getColliderBoundsAt(Tmpl8::vec2& pos) { return collidingBox_.at(pos); }

	Tmpl8::vec2 getColliderPos() { return collidingBox_.getPos(); }
	Tmpl8::vec2 getColliderSize() { return collidingBox_.getSize(); }

	Signal<> onCollisionStart{};
	Signal<> onCollisionEnd{};
protected:
	BoundingBox collidingBox_;
};