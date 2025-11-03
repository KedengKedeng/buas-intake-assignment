#include "object.hpp"

Object::Object(Tmpl8::vec2 pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox) :
	pos_(pos), boundingBox_(boundingBox), interactionBoundingBox_(interactionBoundingBox) {
	subscribe();
};

Object::~Object() {
	printf("fsd");
	unsubscribe();
}

void Object::subscribe() {
	onInteractionStartUnsub = interactionBoundingBox_.onIntersectStart.subscribe([this]() {onInteractStart(); });
	onInteractionStartUnsub = interactionBoundingBox_.onIntersectEnd.subscribe([this]() {onInteractEnd(); });
}

void Object::unsubscribe() {
	onInteractionStartUnsub();
	onInteractionEndUnsub();
}