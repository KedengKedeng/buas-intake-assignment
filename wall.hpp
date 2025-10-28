#pragma once
#include "object.hpp"

class Wall : public Object {
public:
	Wall(Tmpl8::vec2 pos, Tmpl8::vec2 size) :
		Object(pos, BoundingBox(Tmpl8::vec2(0), size), ObservableBoundingBox()) {
		allowInteraction = false;
	};
	void draw(Tmpl8::Surface* surface) override;
	void process() override {};
};