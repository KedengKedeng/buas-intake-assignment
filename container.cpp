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
	scrollbar_(0, pos_ + vec2(size.x, 0.0f), vec2(20.0f, size_.y), size_, [this](vec2<float> offset) {scrollOffset = offset; })
{ };

void Container::setPos(vec2<float>& pos) {
	vec2 delta = pos_ - pos;
	for (auto& it = begin(); it != end(); it++)
		it->second->setPos(it->second->getPos() + delta);
	pos_ = pos;
	spreadObjects();
}

void Container::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	if (scrollable_) {
		// use another surface to contain everything within the context
		// of the container
		drawingSurface->Clear(0x00);

		for (auto& object : objects_)
			object.second->draw(drawingSurface.get(), offset - scrollOffset - pos_ + 1);

		drawingSurface->BlendCopyTo(surface, static_cast<int>(floor(pos_.x)) - 1, static_cast<int>(floor(pos_.y)) - 1);
		scrollbar_.draw(surface, offset);
	}
	else {
		// draw normally
		for (auto& object : objects_)
			object.second->draw(surface, offset);
	}
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
	for (auto& object : objects_) {
		auto subscriber = std::dynamic_pointer_cast<SubscriptionManager>(object.second);
		if (subscriber != nullptr) subscriber->subscribe();
	}

	if (scrollable_) scrollbar_.subscribe();
}

void Container::unsubscribe() {
	SubscriptionManager::unsubscribe();

	for (auto& object : objects_) {
		auto subscriber = std::dynamic_pointer_cast<SubscriptionManager>(object.second);
		if (subscriber != nullptr) subscriber->unsubscribe();
	}

	scrollbar_.unsubscribe();
}

void Container::spreadObjects() {
	if (justification_ == Justification::NONE) return;

	// get combined size of all elements
	vec2<float> combinedSize(0.0f);
	for (auto& object : objects_) combinedSize += object.second->getSize();

	// spread objects by gap
	vec2<float> currentPos = pos_;
	for (auto& object : objects_) {
		object.second->setPos(currentPos);

		vec2<float> objectSize = object.second->getSize();
		if (justification_ == Justification::VERTICAL) currentPos.y += objectSize.y + gap_.y;
		if (justification_ == Justification::HORIZONTAL) currentPos.x += objectSize.x + gap_.x;
	}

	scrollbar_.setParentSize(vec2(std::max(currentPos.x - pos_.x, size_.x), std::max(currentPos.y - pos_.y, size_.y)));
}