#include "container.hpp"

Container::Container(
	int64_t id,
	Tmpl8::vec2& pos,
	Tmpl8::vec2& size,
	Justification justification
)
	: Object(id, pos, BoundingBox(Tmpl8::vec2(0), size), ObservableBoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(0))), justification_(justification) { };

void Container::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	for (auto& object : objects_)
		object.second->draw(surface, offset);
}

void Container::process(float deltaTime) {
	for (auto& object : objects_)
		object.second->process(deltaTime);
}

void Container::insertObject(std::unique_ptr<Object> object) {
	int64_t id = object->getId();
	objects_[id] = std::move(object);
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
	Tmpl8::vec2 combinedSize(0);
	for (auto& object : objects_) combinedSize += object.second->getBounds().getSize();

	// calculate the gap between each element based on how much space
	// they take up combined compared to the container size
	Tmpl8::vec2 containerSize = boundingBox_.getSize();
	Tmpl8::vec2 gap = (containerSize - combinedSize) / static_cast<float>(objects_.size());

	// spread objects by gap
	Tmpl8::vec2 currentPos = pos_;
	for (auto& object : objects_) {
		object.second->setPos(currentPos);

		Tmpl8::vec2 objectSize = object.second->getBounds().getSize();
		if (justification_ == Justification::VERTICAL) currentPos.y += objectSize.y + gap.y;
		if (justification_ == Justification::HORIZONTAL) currentPos.x += objectSize.x + gap.x;
	}
}