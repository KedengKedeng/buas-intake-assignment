#pragma once
#include "object.hpp"

class TestWall : public Object {
public:
	TestWall(int x, int y) : Object(x, y, BoundingBox(Tmpl8::vec2(0, 0), Tmpl8::vec2(20, 20))) {};
	void draw(Tmpl8::Surface* surface) override;
	void process() override {};
};