#include "button.hpp"

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