#pragma once
#include "boundingBox.hpp"
#include "signal.hpp"

class Interactable {
public:
	Interactable () : interactionBox_(), isInteractor_(false) {}
	Interactable(const vec2<float>& pos, const vec2<float>& size, bool isInteractor) :
		interactionBox_(pos, size), isInteractor_(isInteractor) {}

	BoundingBox getInteractableBounds() { return interactionBox_; }
	BoundingBox getInteractableBoundsAt(vec2<float>& pos) { return interactionBox_.at(pos); }

	vec2<float> getInteractablePos() { return interactionBox_.getPos(); }
	vec2<float> getInteractableSize() { return interactionBox_.getSize(); }

	bool isInteractor() { return isInteractor_; }

	Signal<> onInteractionStart{};
	Signal<> onInteractionEnd{};
protected:
	bool isInteractor_;
	BoundingBox interactionBox_;
};