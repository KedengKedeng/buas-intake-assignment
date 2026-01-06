#pragma once
#include "object.hpp"
#include "collider.hpp"

class Wall : public Object, public Collider {
public:
	Wall(int64_t id, const Tmpl8::vec2& pos, const Tmpl8::vec2& size) :
		Object(id, pos, size), Collider(Tmpl8::vec2(0), size) {};

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
};