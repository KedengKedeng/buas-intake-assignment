#pragma once
#include "boundingBox.hpp"
#include "signal.hpp"

// this is really just a bounding box with intersection signals
class ObservableBoundingBox : public BoundingBox {
public:
	ObservableBoundingBox() : BoundingBox() {}
	ObservableBoundingBox(const Tmpl8::vec2& pos, const Tmpl8::vec2& size) : BoundingBox(pos, size) {}

	ObservableBoundingBox at(Tmpl8::vec2& pos) { return ObservableBoundingBox(pos + pos_, size_); }

	Signal<> onIntersectStart{};
	Signal<> onIntersectEnd{};
};