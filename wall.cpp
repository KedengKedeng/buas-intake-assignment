#include "wall.hpp"

void Wall::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Bar(
		pos_ + offset,
		pos_ + offset + size_,
		0xffffff
	);
}