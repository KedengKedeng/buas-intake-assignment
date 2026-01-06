#include "button.hpp"

Button::Button(
	int64_t id,
	std::function<void()> handler,
	const std::string& text,
	Tmpl8::vec2& pos,
	Tmpl8::vec2& size,
	int borderWidth,
	Tmpl8::Pixel color,
	Tmpl8::Pixel borderColor
) :
	Object(id, pos, size),
	handler_(handler),
	text_(text),
	borderWidth_(borderWidth),
	color_(color),
	borderColor_(borderColor)
{};

void Button::subscribe() {
	Object::subscribe();

	unsubscribers.push_back(onMouseDown.subscribe([this](Tmpl8::vec2& pos) {
		BoundingBox absolutePosBounds = BoundingBox(pos_, size_);
		BoundingBox mouseBounds = BoundingBox(pos, Tmpl8::vec2(1));

		if (absolutePosBounds.isInBounds(mouseBounds))
			active = true;
	}));

	unsubscribers.push_back(onMouseUp.subscribe([this]() {
		if (active) handler_();

		active = false;
	}));
}

void Button::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
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

	int textLeft = static_cast<int>(pos_.x + (size_.x - text_.size() * 6 ) / 2);
	int textTop = static_cast<int>(pos_.y + (size_.y - 6) / 2);
	surface->Print(const_cast<char*>(text_.c_str()), textLeft, textTop, 0x000000);
}