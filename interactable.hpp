#pragma once
#include "boundingBox.hpp"

class Interactable {
public:
	Interactable () : interactionBox_(), isInteractor_(false) {}
	Interactable(const Tmpl8::vec2& pos, const Tmpl8::vec2& size, bool isInteractor) :
		interactionBox_(pos, size), isInteractor_(isInteractor) {}

	BoundingBox getInteractableBounds() { return interactionBox_; }
	BoundingBox getInteractableBoundsAt(Tmpl8::vec2& pos) { return interactionBox_.at(pos); }

	Tmpl8::vec2 getInteractablePos() { return interactionBox_.getPos(); }
	Tmpl8::vec2 getInteractableSize() { return interactionBox_.getSize(); }

	bool isInteractor() { return isInteractor_; }

	Signal<> onInteractionStart{};
	Signal<> onInteractionEnd{};
protected:
	bool isInteractor_;
	BoundingBox interactionBox_;
};