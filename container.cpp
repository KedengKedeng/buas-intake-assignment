#include "container.hpp"

Container::Container(
	int64_t id,
	vec2<float>& pos,
	vec2<float>& size,
	Justification justification
)
	: Object(id, pos, size), justification_(justification) { };

void Container::setPos(vec2<float>& pos) {
	vec2 delta = pos_ - pos;
	for (auto& it = begin(); it != end(); it++)
		it->second->setPos(it->second->getPos() + delta);
	pos_ = pos;
	spreadObjects();
}

void Container::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	for (auto& object : objects_)
		object.second->draw(surface, offset);
}

void Container::process(float deltaTime) {
	for (auto& object : objects_)
		object.second->process(deltaTime);
}

void Container::insertObject(std::shared_ptr<Object> object) {
	int64_t id = object->getId();
	objects_[id] = object;
	spreadObjects();
}

void Container::subscribe() {
	for (auto& object : objects_) object.second->subscribe();
}

void Container::unsubscribe() {
	Object::unsubscribe();

	for (auto& object : objects_) object.second->unsubscribe();
}

void Container::spreadObjects() {
	if (justification_ == Justification::NONE) return;

	// get combined size of all elements
	vec2<float> combinedSize(0.0f);
	for (auto& object : objects_) combinedSize += object.second->getSize();

	// calculate the gap between each element based on how much space
	// they take up combined compared to the container size
	vec2<float> gap = (size_ - combinedSize) / static_cast<float>(objects_.size());

	// spread objects by gap
	vec2<float> currentPos = pos_;
	for (auto& object : objects_) {
		object.second->setPos(currentPos);

		vec2<float> objectSize = object.second->getSize();
		if (justification_ == Justification::VERTICAL) currentPos.y += objectSize.y + gap.y;
		if (justification_ == Justification::HORIZONTAL) currentPos.x += objectSize.x + gap.x;
	}
}