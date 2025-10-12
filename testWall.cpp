#include "testWall.hpp"

void TestWall::draw(Tmpl8::Surface* surface) {
	Tmpl8::vec2 size = boundingBox_.getSize();
	surface->Bar(x_, y_, x_ + size.x, y_ + size.y, 0xffffff);
}