#include "testWall.hpp"

void TestWall::draw(Tmpl8::Surface* surface) {
	surface->Bar(x_, y_, x_ + 20, y_ + 20, 0xffffff);
}