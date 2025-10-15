#include "button.hpp"

void Button::draw(Tmpl8::Surface* surface) {
	Tmpl8::vec2 size = boundingBox_.getSize();
	surface->Bar(x_, y_, x_ + size.x, y_ + size.y, borderColor_);
	surface->Bar(
		x_ + borderWidth_, 
		y_ + borderWidth_, 
		x_ + size.x - borderWidth_, 
		y_ + size.y - borderWidth_, 
		color_
	);

	surface->Print(const_cast<char*>(text_.c_str()), x_, y_, 0x000000);
}