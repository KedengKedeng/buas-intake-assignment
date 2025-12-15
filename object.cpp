#include "object.hpp"

Object::Object(int64_t id, Tmpl8::vec2& pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox) :
	id_(id), pos_(pos), boundingBox_(boundingBox), interactionBoundingBox_(interactionBoundingBox) {};

Object::~Object() {
	unsubscribe();
}

void Object::subscribe() {
	unsubscribers.push_back(interactionBoundingBox_.onIntersectStart.subscribe([this]() {onInteractStart(); }));
	unsubscribers.push_back(interactionBoundingBox_.onIntersectEnd.subscribe([this]() {onInteractEnd(); }));
}

void Object::unsubscribe() {
	for (auto& unsubscriber : unsubscribers) unsubscriber();
	unsubscribers.clear();
}