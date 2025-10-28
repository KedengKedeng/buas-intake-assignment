#include "object.hpp"

Object::Object(Tmpl8::vec2 pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox) :
	pos_(pos), boundingBox_(boundingBox), interactionBoundingBox_(interactionBoundingBox) {
	interactionBoundingBox_.onIntersectStart.subscribe([this]() {onInteractStart(); });
	interactionBoundingBox_.onIntersectEnd.subscribe([this]() {onInteractEnd(); });
};