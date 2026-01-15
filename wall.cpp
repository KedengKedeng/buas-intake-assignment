#include "wall.hpp"

void Wall::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Bar(
		static_cast<int>(pos_.x + offset.x), 
		static_cast<int>(pos_.y + offset.y),
		static_cast<int>(pos_.x + offset.x + size_.x),
		static_cast<int>(pos_.y + offset.y + size_.y),
		0xffffff
	);
}