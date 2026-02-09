#pragma once
#include "collider.hpp"

// return the min and max of the position as the user of the function most choose which they want
Rect2<float> Collider::getColliderPos() const {
	vec2 minPos(std::numeric_limits<float>::infinity());
	vec2 maxPos(-std::numeric_limits<float>::infinity());

	for (auto& box : collidingBoxes_) {
		auto boxPos = box.getPos();
		minPos.x = std::min(minPos.x, boxPos.x);
		minPos.y = std::min(minPos.y, boxPos.y);
		maxPos.x = std::max(maxPos.x, boxPos.x);
		maxPos.y = std::max(maxPos.y, boxPos.y);
	}

	return Rect2(minPos.x, minPos.y, maxPos.x - minPos.x, maxPos.y - minPos.y);
}

// same as above but for size
Rect2<float> Collider::getColliderSize() const {
	vec2 minSize(std::numeric_limits<float>::infinity());
	vec2 maxSize(-std::numeric_limits<float>::infinity());

	for (auto& box : collidingBoxes_) {
		auto boxSize = box.getSize();
		minSize.x = std::min(minSize.x, boxSize.x);
		minSize.y = std::min(minSize.y, boxSize.y);
		maxSize.x = std::max(maxSize.x, boxSize.x);
		maxSize.y = std::max(maxSize.y, boxSize.y);
	}

	return Rect2(minSize.x, minSize.y, maxSize.x, maxSize.y);
}

void Collider::addCollider(const BoundingBox& box) {
	collidingBoxes_.push_back(box);
}

vec2<float> Collider::swept(Collider& other, vec2<float> velocity, vec2<float> at, vec2<float> otherAt) const {
	auto collisionVec = velocity;

	for (auto& box : collidingBoxes_) {
		for (auto& otherBox = other.begin(); otherBox != other.end(); otherBox++) {
			CollisionResult result = box.at(at).swept(otherBox->at(otherAt), velocity);
			if (result.collision) {
				vec2 allowedMovement(0.0f);

				allowedMovement.x += velocity.x * result.time;
				allowedMovement.y += velocity.y * result.time;

				// Check for remaining times in case of diagonal movement.
				float remainingTime = 1 - result.time;
				if (result.normalX == 0.0f) allowedMovement.x += velocity.x * remainingTime;
				if (result.normalY == 0.0f) allowedMovement.y += velocity.y * remainingTime;

				// Compare to collisions beforehand so the minimum collision in a direction is always chosen.
				if (velocity.x >= 0.0f) collisionVec.x = std::min(collisionVec.x, allowedMovement.x);
				else collisionVec.x = std::max(collisionVec.x, allowedMovement.x);

				if (velocity.y >= 0.0f) collisionVec.y = std::min(collisionVec.y, allowedMovement.y);
				else collisionVec.y = std::max(collisionVec.y, allowedMovement.y);
			}
		}
	}

	return collisionVec;
}

void Collider::drawColliders(Tmpl8::Surface& surface, const vec2<float>& offset) {
	for (auto& box : collidingBoxes_) {
		auto pos = box.getPos() + offset;
		surface.Box(pos, pos + box.getSize(), 0xff0000ff);
	}
}