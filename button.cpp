#include "button.hpp"

Button::Button(
	std::function<void()> handler,
	std::string& text,
	Tmpl8::vec2 pos,
	Tmpl8::vec2 size,
	int borderWidth,
	Tmpl8::Pixel color,
	Tmpl8::Pixel borderColor
) :
	Object(pos, BoundingBox(Tmpl8::vec2(0), size), ObservableBoundingBox()),
	handler_(handler),
	text_(text),
	borderWidth_(borderWidth),
	color_(color),
	borderColor_(borderColor)
{
	mousePressed.subscribe([this](Tmpl8::vec2& pos) {
		BoundingBox absolutePosBounds = boundingBox_.at(pos_);
		BoundingBox mouseBounds = BoundingBox(pos, Tmpl8::vec2(1));

		if (absolutePosBounds.isInBounds(mouseBounds))
			active = true;
		});

	mouseReleased.subscribe([this]() {
		if (active)
			handler_();

		active = false;
		});
};

void Button::draw(Tmpl8::Surface* surface) {
	Tmpl8::vec2 size = boundingBox_.getSize();
	surface->Bar(pos_.x, pos_.y, pos_.x + size.x, pos_.y + size.y, borderColor_);
	surface->Bar(
		pos_.x + borderWidth_, 
		pos_.y + borderWidth_, 
		pos_.x + size.x - borderWidth_, 
		pos_.y + size.y - borderWidth_, 
		color_
	);

	surface->Print(const_cast<char*>(text_.c_str()), pos_.x, pos_.y, 0x000000);
}