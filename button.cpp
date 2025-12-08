#include "button.hpp"

Button::Button(
	int64_t id,
	std::function<void()> handler,
	std::string& text,
	Tmpl8::vec2& pos,
	Tmpl8::vec2& size,
	int borderWidth,
	Tmpl8::Pixel color,
	Tmpl8::Pixel borderColor
) :
	Object(id, pos, BoundingBox(Tmpl8::vec2(0), size), ObservableBoundingBox()),
	handler_(handler),
	text_(text),
	borderWidth_(borderWidth),
	color_(color),
	borderColor_(borderColor)
{};

void Button::subscribe() {
	Object::subscribe();

	onMouseDownUnsub = onMouseDown.subscribe([this](Tmpl8::vec2& pos) {
		BoundingBox absolutePosBounds = boundingBox_.at(pos_);
		BoundingBox mouseBounds = BoundingBox(pos, Tmpl8::vec2(1));

		if (absolutePosBounds.isInBounds(mouseBounds))
			active = true;
	});

	onMouseUpUnsub = onMouseUp.subscribe([this]() {
		if (active) handler_();

		active = false;
	});
}

void Button::unsubscribe() {
	Object::unsubscribe();

	onMouseDownUnsub();
	onMouseUpUnsub();
}

void Button::draw(Tmpl8::Surface* surface) {
	Tmpl8::vec2 size = boundingBox_.getSize();

	int left = static_cast<int>(pos_.x);
	int top = static_cast<int>(pos_.y);
	int right = static_cast<int>(pos_.x + size.x);
	int bottom = static_cast<int>(pos_.y + size.y);
	surface->Bar(left, top, right, bottom, borderColor_);
	surface->Bar(
		left + borderWidth_, 
		top + borderWidth_, 
		right - borderWidth_, 
		bottom - borderWidth_, 
		color_
	);

	surface->Print(const_cast<char*>(text_.c_str()), left, top, 0x000000);
}