#include "testWall.hpp"

void TestWall::draw(Tmpl8::Surface* surface) {
	Tmpl8::vec2 size = boundingBox_.getSize();
	surface->Bar(pos_.x, pos_.y, pos_.x + size.x, pos_.y + size.y, 0xffffff);
}