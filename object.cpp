#include "object.hpp"

Object::Object(int64_t id, const vec2<float>& pos, const vec2<float>& size) :
	id_(id), pos_(pos), size_(size) {};

Object::~Object() {
	unsubscribe();
}

void Object::unsubscribe() {
	for (auto& unsubscriber : unsubscribers) unsubscriber();
	unsubscribers.clear();
}