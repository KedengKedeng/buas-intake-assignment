#include "wall.hpp"

void Wall::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	Tmpl8::vec2 size = collidingBox_.getSize();
	surface->Bar(
		static_cast<int>(pos_.x + offset.x), 
		static_cast<int>(pos_.y + offset.y),
		static_cast<int>(pos_.x + offset.x + size.x),
		static_cast<int>(pos_.y + offset.y + size.y),
		0xffffff
	);
}