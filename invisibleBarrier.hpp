#pragma once
#include "object.hpp"
#include "collider.hpp"

class InvisibleBarrier : public Object, public Collider {
public:
	InvisibleBarrier(int64_t id, const Tmpl8::vec2& pos, const Tmpl8::vec2& size) :
		Object(id, pos, ObservableBoundingBox()), Collider(Tmpl8::vec2(0), size) {
		allowInteraction = false;
	};

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override {};
};