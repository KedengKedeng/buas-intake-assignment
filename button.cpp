#include "button.hpp"
#include "mouseSignals.hpp"
#include "boundingBox.hpp"

Button::Button(
	int64_t id,
	std::function<void()> handler,
	const std::string& text,
	vec2<float>& pos,
	vec2<float>& size,
	int borderWidth,
	Tmpl8::Pixel color,
	Tmpl8::Pixel borderColor
) :
	Object(id, pos, size),
	handler_(handler),
	text_(Text(const_cast<std::string&>(text), 1, 0x00)),
	borderWidth_(borderWidth),
	color_(color),
	borderColor_(borderColor)
{};

void Button::subscribe() {
	Object::subscribe();

	unsubscribers.push_back(onMouseDown.subscribe([this](vec2<float>& pos) {
		BoundingBox absolutePosBounds(pos_, size_);

		if (absolutePosBounds.isInBounds(pos))
			active = true;
	}));

	unsubscribers.push_back(onMouseUp.subscribe([this]() {
		if (active) handler_();

		active = false;
	}));
}

void Button::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	int left = static_cast<int>(pos_.x);
	int top = static_cast<int>(pos_.y);
	int right = static_cast<int>(pos_.x + size_.x);
	int bottom = static_cast<int>(pos_.y + size_.y);
	surface->Bar(left, top, right, bottom, borderColor_);
	surface->Bar(
		left + borderWidth_, 
		top + borderWidth_, 
		right - borderWidth_, 
		bottom - borderWidth_, 
		color_
	);

	float textLeft = pos_.x + (size_.x - text_.getWidth()) / 2;
	float textTop = pos_.y + (size_.y - text_.getHeight()) / 2;
	text_.draw(surface, vec2(textLeft, textTop));
}