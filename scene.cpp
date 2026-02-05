#include "scene.hpp"
#include "collider.hpp"
#include "interactable.hpp"
#include "objectSignals.hpp"

void Scene::process(float deltaTime) {
	ObjectContainer::process(deltaTime);

	// Process the entire queue
	for (; !queue.empty(); queue.pop()) {
		auto func = queue.front();
		func();
	}
}

void Scene::subscribe() {
	ObjectContainer::subscribe();
	drawDispatcher_.subscribe();

	addSubscription(deleteObjectSignal.subscribe([this](int64_t id) {
		queue.push([this, id]() {deleteObject(id); });
	}));

	addSubscription(createObjectSignal.subscribe([this](std::shared_ptr<Object> object) {
		insertObject(object);
		auto subscriber = std::dynamic_pointer_cast<SubscriptionManager>(object);
		if (subscriber == nullptr) return;
		subscriber->subscribe();
	}));
}

void Scene::unsubscribe() {
	ObjectContainer::unsubscribe();
	drawDispatcher_.unsubscribe();
	// not clearing between scene transitions causes some weird behavior.
	// hence we clear just to be sure.
	keyboardInput_.clearKeysDown();
}

vec2<float> Scene::objectsCollideWithBounds(const Object& object, vec2<float> velocity) const {
	// check if object has collider functionality
	const Collider* const collider = dynamic_cast<const Collider* const>(&object);
	if (collider == nullptr) return vec2(0.0f);

	auto collisionVec = velocity;

	for (auto& [id, object2] : objects_) {
		// check if object has collider functionality
		auto collider2 = getObject<Collider>(id);

		// the colliding object can be in this list and can hence check collision with itself.
		// it would never be able to move if we dont check for this.
		if (object.getId() == id || collider2 == nullptr) continue;

		vec2 result = collider->swept(*(collider2.get()), velocity, object.getPos(), object2->getPos());

		// Compare to collisions beforehand so the minimum collision in a direction is always chosen.
		if (velocity.x >= 0.0f) collisionVec.x = std::min(collisionVec.x, result.x);
		else collisionVec.x = std::max(collisionVec.x, result.x);

		if (velocity.y >= 0.0f) collisionVec.y = std::min(collisionVec.y, result.y);
		else collisionVec.y = std::max(collisionVec.y, result.y);
	}

	return collisionVec;
}

void Scene::interactionCheck(const Object& object) {
	// check if object has interactable functionality
	const Interactable* const interactor = dynamic_cast<const Interactable*>(&object);
	if (interactor == nullptr || !interactor->isInteractor()) return;

	for (auto& [id, object2] : objects_) {
		// check if object has interactable functionality
		auto interacted = getObject<Interactable>(id);
		if (interacted == nullptr) continue;

		BoundingBox interactorBounds = interactor->getInteractableBoundsAt(object.getPos());
		BoundingBox interactedBounds = interacted->getInteractableBoundsAt(object2->getPos());
		bool result = interactorBounds.isInBounds(interactedBounds);

		bool foundInteractingObject = alreadyInteracting.find(id) != alreadyInteracting.end();
		// add to a list of already interacting objects.
		// if not kept track it would emit onIntersectStart every frame
		if (result && !foundInteractingObject) {
			alreadyInteracting.insert(id);
			interacted->onInteractionStart.emit();
		}

		// remove from list if no longer interacting
		if (!result && foundInteractingObject) {
			alreadyInteracting.erase(id);
			interacted->onInteractionEnd.emit();
		}
	}\
}