#pragma once
#include "object.hpp"

class Wall : public Object {
public:
	Wall(int64_t id, const Tmpl8::vec2& pos, const Tmpl8::vec2& size) :
		Object(id, pos, BoundingBox(Tmpl8::vec2(0), size), ObservableBoundingBox()) {
		allowInteraction = false;
	};

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
};