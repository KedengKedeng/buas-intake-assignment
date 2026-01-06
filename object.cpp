#include "object.hpp"

Object::Object(int64_t id, const Tmpl8::vec2& pos, const Tmpl8::vec2& size) :
	id_(id), pos_(pos), size_(size) {};

Object::~Object() {
	unsubscribe();
}

void Object::unsubscribe() {
	for (auto& unsubscriber : unsubscribers) unsubscriber();
	unsubscribers.clear();
}