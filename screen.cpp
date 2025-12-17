#include "screen.hpp"

void Screen::process(float deltaTime) {
	Container::process(deltaTime);

	// Process the entire queue
	for (; !queue.empty(); queue.pop()) {
		auto func = queue.front();
		func();
	}
}

void Screen::unsubscribe() {
	Container::unsubscribe();
	keyboardInput_.clearKeysDown();
}

Tmpl8::vec2 Screen::objectsCollideWithBounds(Object& object, Tmpl8::vec2& velocity) {
	BoundingBox bounds = object.getAbsoluteBounds();

	Tmpl8::vec2 collisionVec = velocity;

	for (auto& it = objects_.begin(); it != objects_.end(); it++) {
		auto object2 = it->second.get();

		// the colliding object can be in this list and can hence check collision with itself.
		// it would never be able to move if we dont check for this.
		if (object.getId() == object2->getId() || !object2->isCollisionAllowed()) continue;

		CollisionResult result = bounds.swept(object2->getAbsoluteBounds(), velocity);
		if (result.collision) {
			Tmpl8::vec2 allowedMovement(0, 0);

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

	return collisionVec;
}

void Screen::interactionCheck(ObservableBoundingBox& bounds) {
	for (auto& it = objects_.begin(); it != objects_.end(); it++) {
		auto object = it->second.get();
		if (!object->isInteractionAllowed()) continue;

		ObservableBoundingBox& objectBounds = object->getInteractionBounds();
		bool result = bounds.isInBounds(object->getAbsoluteInteractionBounds());

		bool foundInteractingObject = alreadyInteracting.find(it->first) != alreadyInteracting.end();
		// add to a list of already interacting objects.
		// if not kept track it would emit onIntersectStart every frame
		if (result && !foundInteractingObject) {
			alreadyInteracting.insert(it->first);
			objectBounds.onIntersectStart.emit();
		}

		// remove from list if no longer interacting
		if (!result && foundInteractingObject) {
			alreadyInteracting.erase(it->first);
			objectBounds.onIntersectEnd.emit();
		}
	}
}