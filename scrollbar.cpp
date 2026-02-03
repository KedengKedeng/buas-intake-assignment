#include "scrollbar.hpp"
#include "boundingBox.hpp"

Scrollbar::Scrollbar(int64_t id, vec2<float>& pos, vec2<float>& size, vec2<float>& parentSize, std::function<void(vec2<float>)> onDrag) :
	Object(id, pos, size),
	mouseHandler_(),
	parentSize_(parentSize),
	thumbPos_(0),
	thumbSize_(getThumbSize()),
	onDrag_(onDrag)
{
	mouseHandler_.setInteractionCheck([this](vec2<float>& pos) {
		return BoundingBox(getPos(), getSize()).isInBounds(pos);
	});

	mouseHandler_.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		auto objectPos = getPos();
		auto objectSize = getSize();
		thumbPos_ = std::max(std::min(pos.y, objectPos.y + objectSize.y - thumbSize_), objectPos.y);
		onDrag_(vec2(0.0f, (thumbPos_ - objectPos.y) / objectSize.y * parentSize_.y));
	});
}

void Scrollbar::setParentSize(vec2<float>& size) {
	parentSize_ = size;
	thumbSize_ = getThumbSize();
	thumbPos_ = getPos().y;
}

void Scrollbar::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto pos = getPos() + offset;
	auto size = getSize();
	surface->Bar(pos, pos + size, 0xffb6b8ae);

	vec2 thumbPos = vec2(pos.x, thumbPos_ + offset.y);
	surface->Bar(thumbPos, thumbPos + vec2(size.x, thumbSize_), 0xff000000);
}

void Scrollbar::subscribe() {
	SubscriptionManager::subscribe();

	mouseHandler_.subscribe();
}

void Scrollbar::unsubscribe() {
	SubscriptionManager::unsubscribe();

	mouseHandler_.unsubscribe();
}

float Scrollbar::getThumbSize() {
	auto size = getSize();
	return size.y * (size.y / parentSize_.y);
}