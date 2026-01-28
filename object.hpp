#pragma once
#include "surface.h"
#include "vec2.hpp"

class Object {
public:
	Object(int64_t id, const vec2<float>& pos, const vec2<float>& size) :
		id_(id), pos_(pos), size_(size) {};

	int64_t getId() { return id_; }

	virtual void setPos(vec2<float>& pos) { pos_ = pos; }
	vec2<float> getPos() { return pos_; }
	void setSize(vec2<float>& size) { size_ = size; }
	vec2<float> getSize() { return size_; }

	virtual void draw(Tmpl8::Surface* surface, const vec2<float>& offset) = 0;
	virtual void process(float deltaTime) {};
protected:
	vec2<float> pos_, size_;
private:
	int64_t id_;
};