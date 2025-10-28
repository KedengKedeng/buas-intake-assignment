#pragma once
#include "boundingBox.hpp"
#include "signal.hpp"

class ObservableBoundingBox : public BoundingBox {
public:
	ObservableBoundingBox() : BoundingBox() {}
	ObservableBoundingBox(Tmpl8::vec2 pos, Tmpl8::vec2 size) : BoundingBox(pos, size) {}

	ObservableBoundingBox at(Tmpl8::vec2 pos) { return ObservableBoundingBox(pos + pos_, size_); }

	Signal<> onIntersectStart{};
	Signal<> onIntersectEnd{};
};