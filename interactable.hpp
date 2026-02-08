#pragma once
#include "boundingBox.hpp"
#include "signal.hpp"

class Interactable {
public:
	Interactable () : interactionBox_(), isInteractor_(false) {}
	Interactable(vec2<float> pos, vec2<float> size, bool isInteractor) :
		interactionBox_(pos, size), isInteractor_(isInteractor) {
		onInteractionStart.subscribe([this]() {isInteracting = true; });
		onInteractionEnd.subscribe([this]() {isInteracting = false; });
	}

	const BoundingBox& getInteractableBounds() const { return interactionBox_; }
	BoundingBox getInteractableBoundsAt(vec2<float> pos) const { return interactionBox_.at(pos); }

	vec2<float> getInteractablePos() const { return interactionBox_.getPos(); }
	vec2<float> getInteractableSize() const { return interactionBox_.getSize(); }

	bool isInteractor() const { return isInteractor_; }

	Signal<> onInteractionStart{};
	Signal<> onInteractionEnd{};
protected:
	BoundingBox interactionBox_;
	bool isInteractor_;

	bool isInteracting = false;
};