#include "wall.hpp"

void Wall::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	auto size = getSize();
	surface->Bar(pos, pos + size, 0xffffffff);
}