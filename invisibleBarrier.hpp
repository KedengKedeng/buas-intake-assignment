#pragma once
#include "object.hpp"
#include "collider.hpp"

class InvisibleBarrier : public Object, public Collider {
public:
	InvisibleBarrier(int64_t id, vec2<float> pos, vec2<float> size) :
		Object(id, pos, size), Collider(vec2(0.0f), size) {};

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override {};
};