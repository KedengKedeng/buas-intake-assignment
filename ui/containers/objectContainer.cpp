#include "objectContainer.hpp"
#include "boundingBox.hpp"

ObjectContainer::ObjectContainer(
	int64_t id,
	vec2<float> pos,
	vec2<float> size,
	Justification justification,
	vec2<float> gap,
	bool scrollable
) : 
	Object(id, pos, size),
	Clickable(true),
	justification_(justification), 
	gap_(gap),
	drawingSurface(Tmpl8::Surface(scrollable ? static_cast<int>(size.x) + 1 : 0, scrollable ? static_cast<int>(size.y) + 1 : 0)),
	scrollable_(scrollable),
	scrollbar_(0, pos + vec2(size.x, 0.0f), vec2(20.0f, size.y), size, [this](vec2<float> offset) {scrollOffset = offset; })
{ };

ObjectContainer::~ObjectContainer() {
	unsubscribe();
}

void ObjectContainer::setPos(vec2<float> pos) {
	vec2 delta = getPos() - pos;
	for (auto& [id, object] : objects_)
		object->setPos(object->getPos() + delta);
	Object::setPos(pos);
	spreadObjects();
}

void ObjectContainer::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	if (scrollable_) {
		// use another surface to contain everything within the context
		// of the container
		drawingSurface.Clear(0x00);

		auto pos = getPos();

		for (auto& [id, object] : objects_)
			object->draw(drawingSurface, offset - scrollOffset + 1);

		drawingSurface.BlendCopyTo(surface, static_cast<int>(floor(pos.x)) - 1, static_cast<int>(floor(pos.y)) - 1);
		scrollbar_.draw(surface, offset);
	}
	else {
		// draw normally
		for (auto& [id, object] : objects_)
			object->draw(surface, offset);
	}
}

void ObjectContainer::process(float deltaTime) {
	for (auto& [id, object] : objects_)
		object->process(deltaTime);
}

void ObjectContainer::insertObject(std::shared_ptr<Object> object) {
	int64_t id = object->getId();
	objects_[id] = object;
	spreadObjects();
}

void ObjectContainer::deleteObject(int64_t id) {
	objects_.erase(id);
}

void ObjectContainer::onMouseDown(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseDown(pos, screenPos);

	auto offset = scrollable_ ? getPos() - scrollOffset : vec2(0.0f);
	for (auto& [id, object] : objects_) {
		auto clickable = std::dynamic_pointer_cast<Clickable>(object);
		if (clickable == nullptr) continue;

		BoundingBox objBounds(object->getPos() + offset, object->getSize());
		if (clickable->getSkipBoundsCheck() || objBounds.isInBounds(pos)) clickable->onMouseDown(pos - offset, screenPos);
	}


	if (scrollable_ && BoundingBox(scrollbar_.getPos(), scrollbar_.getSize()).isInBounds(pos)) scrollbar_.onMouseDown(pos, screenPos);
};

void ObjectContainer::onMouseUp(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseUp(pos, screenPos);

	auto offset = scrollable_ ? getPos() - scrollOffset : vec2(0.0f);
	for (auto& [id, object] : objects_) {
		auto clickable = std::dynamic_pointer_cast<Clickable>(object);
		if (clickable == nullptr) continue;

		if (clickable->getSkipBoundsCheck() || clickable->getMouseDown()) clickable->onMouseUp(pos - offset, screenPos);
	}

	if (scrollable_ && scrollbar_.getMouseDown()) scrollbar_.onMouseUp(pos, screenPos);
};

void ObjectContainer::onMouseMove(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) {
	Clickable::onMouseMove(pos, screenPos, delta);

	auto offset = scrollable_ ? getPos() - scrollOffset : vec2(0.0f);
	for (auto& [id, object] : objects_) {
		auto clickable = std::dynamic_pointer_cast<Clickable>(object);
		if (clickable == nullptr) continue;
		clickable->onMouseMove(pos - offset, screenPos, delta);
		if (clickable->getMouseDown()) clickable->onMouseDrag(pos - offset, screenPos, delta);
	}

	if (scrollable_ && scrollbar_.getMouseDown()) scrollbar_.onMouseDrag(pos, screenPos, delta);
};

void ObjectContainer::subscribe() {
	for (auto& [id, object] : objects_) {
		auto subscriber = std::dynamic_pointer_cast<SubscriptionManager>(object);
		if (subscriber != nullptr) subscriber->subscribe();
	}
}

void ObjectContainer::unsubscribe() {
	SubscriptionManager::unsubscribe();

	for (auto& [id, object] : objects_) {
		auto subscriber = std::dynamic_pointer_cast<SubscriptionManager>(object);
		if (subscriber != nullptr) subscriber->unsubscribe();
	}
}

void ObjectContainer::spreadObjects() {
	if (justification_ == Justification::NONE) return;

	// get combined size of all elements
	vec2<float> combinedSize(0.0f);
	for (auto& [id, object] : objects_) combinedSize += object->getSize();

	// spread objects by gap
	vec2<float> currentPos = scrollable_ ? vec2(0.0f) : getPos();
	for (auto& [id, object] : objects_) {
		object->setPos(currentPos);

		vec2<float> objectSize = object->getSize();
		if (justification_ == Justification::VERTICAL) currentPos.y += objectSize.y + gap_.y;
		if (justification_ == Justification::HORIZONTAL) currentPos.x += objectSize.x + gap_.x;
	}

	auto pos = currentPos;
	auto size = getSize();
	scrollbar_.setParentSize(vec2(std::max(pos.x, size.x), std::max(pos.y, size.y)));
}