#pragma once
#include "surface.h"
#include "boundingBox.hpp"
#include "observableBoundingBox.hpp"

class Object {
public:
	Object(Tmpl8::vec2 pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox);

	void setPos(Tmpl8::vec2 pos) { pos_ = pos; }

	BoundingBox getBounds() { return boundingBox_; }
	BoundingBox getAbsoluteBounds() { return boundingBox_.at(pos_); }
	ObservableBoundingBox getInteractionBounds() { return interactionBoundingBox_; }
	ObservableBoundingBox getAbsoluteInteractionBounds() { return interactionBoundingBox_.at(pos_); }
	bool isCollisionAllowed() { return allowCollision; }
	bool isInteractionAllowed() { return allowInteraction; }

	virtual void draw(Tmpl8::Surface* surface) = 0;
	virtual void process() = 0;
protected:
	Tmpl8::vec2 pos_;

	BoundingBox boundingBox_;
	ObservableBoundingBox interactionBoundingBox_;
	virtual void onInteractStart() {}
	virtual void onInteractEnd() {}

	bool allowCollision = true;
	bool allowInteraction = true;
};