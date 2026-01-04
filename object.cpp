#include "object.hpp"

Object::Object(int64_t id, const Tmpl8::vec2& pos, ObservableBoundingBox& interactionBoundingBox) :
	id_(id), pos_(pos), interactionBoundingBox_(interactionBoundingBox) {};

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