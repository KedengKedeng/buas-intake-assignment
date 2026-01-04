#pragma once
#include "surface.h"
#include "boundingBox.hpp"
#include "observableBoundingBox.hpp"

class Object {
public:
	Object(int64_t id, const Tmpl8::vec2& pos, ObservableBoundingBox& interactionBoundingBox);
	virtual ~Object();

	int64_t getId() { return id_; }

	void setPos(Tmpl8::vec2& pos) { pos_ = pos; }
	Tmpl8::vec2 getPos() { return pos_; }

	ObservableBoundingBox& getInteractionBounds() { return interactionBoundingBox_; }
	ObservableBoundingBox getAbsoluteInteractionBounds() { return interactionBoundingBox_.at(pos_); }
	bool isInteractionAllowed() { return allowInteraction; }
	bool isInteractor() { return allowInteractor; }

	virtual void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) = 0;
	virtual void process(float deltaTime) {};

	virtual void subscribe();
	virtual void unsubscribe();
protected:
	Tmpl8::vec2 pos_;

	ObservableBoundingBox interactionBoundingBox_;
	virtual void onInteractStart() {};
	virtual void onInteractEnd() {};

	std::vector<std::function<void()>> unsubscribers = {};

	std::function<void()> onInteractionStartUnsub = []() {};
	std::function<void()> onInteractionEndUnsub = []() {};

	bool allowInteraction = true; // allows interactor to interact with this object
	bool allowInteractor = true; // allows the object to be the interactor
private:
	int64_t id_;
};