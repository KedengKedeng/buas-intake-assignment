#include "wall.hpp"

void Wall::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Bar(
		pos_.x + offset.x, 
		pos_.y + offset.y,
		pos_.x + offset.x + size_.x,
		pos_.y + offset.y + size_.y,
		0xffffff
	);
}