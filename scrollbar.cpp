#include "scrollbar.hpp"
#include "boundingBox.hpp"

Scrollbar::Scrollbar(int64_t id, vec2<float>& pos, vec2<float>& size, vec2<float>& parentSize, std::function<void(vec2<float>)> onDrag) :
	Object(id, pos, size),
	mouseMoveHandler_(),
	parentSize_(parentSize),
	thumbPos_(0),
	thumbSize_(getThumbSize()),
	onDrag_(onDrag)
{
	mouseMoveHandler_.setInteractionCheck([this](vec2<float>& pos) {
		return BoundingBox(pos_, size_).isInBounds(pos);
	});

	mouseMoveHandler_.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		thumbPos_ = std::max(std::min(pos.y, pos_.y + size_.y - thumbSize_), pos_.y);
		onDrag_(vec2(0.0f, (thumbPos_ - pos_.y) / (size_.y) * parentSize_.y));
	});
}

void Scrollbar::setParentSize(vec2<float>& size) {
	parentSize_ = size;
	thumbSize_ = getThumbSize();
	thumbPos_ = pos_.y;
}

void Scrollbar::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	vec2 pos = pos_ + offset;
	surface->Bar(pos, pos + size_, 0xffb6b8ae);

	vec2 thumbPos = vec2(pos.x, thumbPos_ + offset.y);
	surface->Bar(thumbPos, thumbPos + vec2(size_.x, thumbSize_), 0xff000000);
}

void Scrollbar::subscribe() {
	SubscriptionManager::subscribe();

	mouseMoveHandler_.subscribe();
}

void Scrollbar::unsubscribe() {
	SubscriptionManager::unsubscribe();

	mouseMoveHandler_.unsubscribe();
}

float Scrollbar::getThumbSize() {
	return size_.y * (size_.y / parentSize_.y);
}