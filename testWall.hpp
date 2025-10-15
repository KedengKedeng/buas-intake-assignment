#pragma once
#include "object.hpp"

class TestWall : public Object {
public:
	TestWall(Tmpl8::vec2 pos, Tmpl8::vec2 size) : Object(pos, BoundingBox(Tmpl8::vec2(0, 0), size)) {};
	void draw(Tmpl8::Surface* surface) override;
	void process() override {};
};