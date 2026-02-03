#include "wall.hpp"

void Wall::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto pos = getPos() + offset;
	auto size = getSize();
	surface->Bar(pos, pos + size, 0xffffffff);
}