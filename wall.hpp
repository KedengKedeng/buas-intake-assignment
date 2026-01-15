#pragma once
#include "object.hpp"
#include "collider.hpp"

class Wall : public Object, public Collider {
public:
	Wall(int64_t id, const vec2<float>& pos, const vec2<float>& size) :
		Object(id, pos, size), Collider(vec2(0.0f), size) {};

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
};