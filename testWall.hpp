#pragma once
#include "object.hpp"

class TestWall : public Object {
public:
	TestWall(int x, int y, int width, int height) : Object(x, y, BoundingBox(Tmpl8::vec2(0, 0), Tmpl8::vec2(width, height))) {};
	void draw(Tmpl8::Surface* surface) override;
	void process() override {};
};