#pragma once
#include "object.hpp"

class Wall : public Object {
public:
	Wall(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size) :
		Object(id, pos, BoundingBox(Tmpl8::vec2(0), size), ObservableBoundingBox()) {
		allowInteraction = false;
	};

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;
};