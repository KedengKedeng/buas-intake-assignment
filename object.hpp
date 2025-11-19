#pragma once
#include "surface.h"
#include "boundingBox.hpp"
#include "observableBoundingBox.hpp"

class Object {
public:
	Object(int64_t id, Tmpl8::vec2& pos, BoundingBox& boundingBox, ObservableBoundingBox& interactionBoundingBox);
	virtual ~Object();

	int64_t getId() { return id_; }

	void setPos(Tmpl8::vec2& pos) { pos_ = pos; }
	Tmpl8::vec2 getPos() { return pos_; }

	BoundingBox& getBounds() { return boundingBox_; }
	BoundingBox getAbsoluteBounds() { return boundingBox_.at(pos_); }
	ObservableBoundingBox& getInteractionBounds() { return interactionBoundingBox_; }
	ObservableBoundingBox getAbsoluteInteractionBounds() { return interactionBoundingBox_.at(pos_); }
	bool isCollisionAllowed() { return allowCollision; }
	bool isInteractionAllowed() { return allowInteraction; }

	virtual void subscribe();
	virtual void unsubscribe();

	virtual void draw(Tmpl8::Surface* surface) = 0;
	virtual void process() {};
protected:
	Tmpl8::vec2 pos_;

	BoundingBox boundingBox_;
	ObservableBoundingBox interactionBoundingBox_;
	virtual void onInteractStart() {}
	virtual void onInteractEnd() {}

	std::function<void()> onInteractionStartUnsub = []() {};
	std::function<void()> onInteractionEndUnsub = []() {};

	bool allowCollision = true;
	bool allowInteraction = true;
private:
	int64_t id_;
};