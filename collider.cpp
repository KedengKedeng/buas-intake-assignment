#pragma once
#include "collider.hpp"

// return the min and max of the position as the user of the function most choose which they want
Rect2<float> Collider::getColliderPos() {
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
Rect2<float> Collider::getColliderSize() {
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

CollisionResult Collider::swept(Collider& other, vec2<float>& velocity, vec2<float>& at, vec2<float>& otherAt) {
	CollisionResult result = { 1.0f, 0, 0, false };

	for (auto& box : collidingBoxes_) {
		for (auto& otherBox = other.begin(); otherBox != other.end(); otherBox++) {
			CollisionResult newResult = box.at(at).swept(otherBox->at(otherAt), velocity);
			if (newResult.collision && std::min(result.time, newResult.time) == newResult.time) result = newResult;
		}
	}

	return result;
}