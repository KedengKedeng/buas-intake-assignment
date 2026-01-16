#pragma once
#include "surface.h"
#include "vec2.hpp"
#include <vector>
#include <functional>

class Object {
public:
	Object(int64_t id, const vec2<float>& pos, const vec2<float>& size);
	virtual ~Object();

	int64_t getId() { return id_; }

	virtual void setPos(vec2<float>& pos) { pos_ = pos; }
	vec2<float> getPos() { return pos_; }
	void setSize(vec2<float>& size) { size_ = size; }
	vec2<float> getSize() { return size_; }

	virtual void draw(Tmpl8::Surface* surface, const vec2<float>& offset) = 0;
	virtual void process(float deltaTime) {};

	virtual void subscribe() {};
	virtual void unsubscribe();
protected:
	vec2<float> pos_, size_;

	std::vector<std::function<void()>> unsubscribers = {};
private:
	int64_t id_;
};