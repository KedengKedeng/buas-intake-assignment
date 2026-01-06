#pragma once
#include "surface.h"
#include "boundingBox.hpp"

class Object {
public:
	Object(int64_t id, const Tmpl8::vec2& pos, const Tmpl8::vec2& size);
	virtual ~Object();

	int64_t getId() { return id_; }

	void setPos(Tmpl8::vec2& pos) { pos_ = pos; }
	Tmpl8::vec2 getPos() { return pos_; }
	void setSize(Tmpl8::vec2& size) { size_ = size; }
	Tmpl8::vec2 getSize() { return size_; }

	virtual void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) = 0;
	virtual void process(float deltaTime) {};

	virtual void subscribe() {};
	virtual void unsubscribe();
protected:
	Tmpl8::vec2 pos_;
	Tmpl8::vec2 size_;

	std::vector<std::function<void()>> unsubscribers = {};
private:
	int64_t id_;
};