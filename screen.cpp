#include "screen.hpp"
#include "collider.hpp"
#include "interactable.hpp"

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
	// not clearing between screen transitions causes some weird behavior.
	// hence we clear just to be sure.
	keyboardInput_.clearKeysDown();
}

Tmpl8::vec2 Screen::objectsCollideWithBounds(Object& object, Tmpl8::vec2& velocity) {
	// check if object has collider functionality
	Collider* collider = dynamic_cast<Collider*>(&object);
	if (collider == nullptr) return Tmpl8::vec2(0, 0);

	BoundingBox bounds = collider->getColliderBoundsAt(object.getPos());

	Tmpl8::vec2 collisionVec = velocity;

	for (auto& it = objects_.begin(); it != objects_.end(); it++) {
		// check if object has collider functionality
		auto object2 = it->second;
		auto collider2 = getObject<Collider>(object2->getId());

		// the colliding object can be in this list and can hence check collision with itself.
		// it would never be able to move if we dont check for this.
		if (object.getId() == object2->getId() || collider2 == nullptr) continue;

		CollisionResult result = bounds.swept(collider2->getColliderBoundsAt(object2->getPos()), velocity);
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

void Screen::interactionCheck(Object& object) {
	// check if object has interactable functionality
	Interactable* interactor = dynamic_cast<Interactable*>(&object);
	if (interactor == nullptr || !interactor->isInteractor()) return;

	for (auto& it = objects_.begin(); it != objects_.end(); it++) {
		auto object2 = it->second;
		// check if object has interactable functionality
		auto interacted = getObject<Interactable>(object2->getId());
		if (interacted == nullptr) continue;

		BoundingBox interactorBounds = interactor->getInteractableBoundsAt(object.getPos());
		BoundingBox interactedBounds = interacted->getInteractableBoundsAt(object2->getPos());
		bool result = interactorBounds.isInBounds(interactedBounds);

		bool foundInteractingObject = alreadyInteracting.find(it->first) != alreadyInteracting.end();
		// add to a list of already interacting objects.
		// if not kept track it would emit onIntersectStart every frame
		if (result && !foundInteractingObject) {
			alreadyInteracting.insert(it->first);
			interacted->onInteractionStart.emit();
		}

		// remove from list if no longer interacting
		if (!result && foundInteractingObject) {
			alreadyInteracting.erase(it->first);
			interacted->onInteractionEnd.emit();
		}
	}
}