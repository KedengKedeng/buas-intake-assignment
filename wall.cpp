#include "wall.hpp"

void Wall::draw(Tmpl8::Surface* surface) {
	Tmpl8::vec2 size = boundingBox_.getSize();
	surface->Bar(
		static_cast<int>(pos_.x), 
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x + size.x),
		static_cast<int>(pos_.y + size.y),
		0xffffff
	);
}