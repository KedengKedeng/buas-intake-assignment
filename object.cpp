#include "object.hpp"

Object::Object(int64_t id, Tmpl8::vec2 pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox) :
	id_(id), pos_(pos), boundingBox_(boundingBox), interactionBoundingBox_(interactionBoundingBox) {
	subscribe();
};

Object::~Object() {
	unsubscribe();
}

void Object::subscribe() {
	onInteractionStartUnsub = interactionBoundingBox_.onIntersectStart.subscribe([this]() {onInteractStart(); });
	onInteractionEndUnsub = interactionBoundingBox_.onIntersectEnd.subscribe([this]() {onInteractEnd(); });
}

void Object::unsubscribe() {
	onInteractionStartUnsub();
	onInteractionEndUnsub();
}