#include "container.hpp"

Container::Container(
	int64_t id,
	vec2<float>& pos,
	vec2<float>& size,
	Justification justification,
	vec2<float>& gap,
	bool scrollable
)
	: Object(id, pos, size),
	justification_(justification), 
	gap_(gap),
	drawingSurface(std::make_shared<Tmpl8::Surface>(scrollable ? static_cast<int>(size.x) + 1 : 0, scrollable ? static_cast<int>(size.y) + 1 : 0)),
	scrollable_(scrollable),
	scrollbar_(0, pos + vec2(size.x, 0.0f), vec2(20.0f, size.y), size, [this](vec2<float> offset) {scrollOffset = offset; })
{ };

void Container::setPos(vec2<float>& pos) {
	vec2 delta = getPos() - pos;
	for (auto& [id, object] : objects_)
		object->setPos(object->getPos() + delta);
	Object::setPos(pos);
	spreadObjects();
}

void Container::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	if (scrollable_) {
		// use another surface to contain everything within the context
		// of the container
		drawingSurface->Clear(0x00);

		auto pos = getPos();

		for (auto& [id, object] : objects_)
			object->draw(drawingSurface.get(), offset - scrollOffset - pos + 1);

		drawingSurface->BlendCopyTo(surface, static_cast<int>(floor(pos.x)) - 1, static_cast<int>(floor(pos.y)) - 1);
		scrollbar_.draw(surface, offset);
	}
	else {
		// draw normally
		for (auto& [id, object] : objects_)
			object->draw(surface, offset);
	}
}

void Container::process(float deltaTime) {
	for (auto& [id, object] : objects_)
		object->process(deltaTime);
}

void Container::insertObject(std::shared_ptr<Object> object) {
	int64_t id = object->getId();
	objects_[id] = object;
	spreadObjects();
}

void Container::subscribe() {
	for (auto& [id, object] : objects_) {
		auto subscriber = std::dynamic_pointer_cast<SubscriptionManager>(object);
		if (subscriber != nullptr) subscriber->subscribe();
	}

	if (scrollable_) scrollbar_.subscribe();
}

void Container::unsubscribe() {
	SubscriptionManager::unsubscribe();

	for (auto& [id, object] : objects_) {
		auto subscriber = std::dynamic_pointer_cast<SubscriptionManager>(object);
		if (subscriber != nullptr) subscriber->unsubscribe();
	}

	scrollbar_.unsubscribe();
}

void Container::spreadObjects() {
	if (justification_ == Justification::NONE) return;

	// get combined size of all elements
	vec2<float> combinedSize(0.0f);
	for (auto& [id, object] : objects_) combinedSize += object->getSize();

	// spread objects by gap
	vec2<float> currentPos = getPos();
	for (auto& [id, object] : objects_) {
		object->setPos(currentPos);

		vec2<float> objectSize = object->getSize();
		if (justification_ == Justification::VERTICAL) currentPos.y += objectSize.y + gap_.y;
		if (justification_ == Justification::HORIZONTAL) currentPos.x += objectSize.x + gap_.x;
	}

	auto pos = currentPos - getPos();
	auto size = getSize();
	scrollbar_.setParentSize(vec2(std::max(pos.x, size.x), std::max(pos.y, size.y)));
}