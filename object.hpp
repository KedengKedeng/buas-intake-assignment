#pragma once
#include "surface.h"
#include "vec2.hpp"

class Object {
public:
	Object(int64_t id, vec2<float> pos, vec2<float> size) :
		id_(id), pos_(pos), size_(size) {};

	virtual ~Object() = default;

	int64_t getId() const { return id_; }

	virtual void setPos(vec2<float> pos) { pos_ = pos; }
	virtual vec2<float> getPos() const { return pos_; }
	virtual void setSize(vec2<float> size) { size_ = size; }
	virtual vec2<float> getSize() const { return size_; }

	virtual void draw(Tmpl8::Surface* surface, vec2<float> offset) const = 0;
	virtual void process(float deltaTime) {};
private:
	int64_t id_;
	vec2<float> pos_, size_;
};