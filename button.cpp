#include "button.hpp"

void Button::draw(Tmpl8::Surface* surface) {
	surface->Bar(x_, y_, x_ + width_, y_ + height_, borderColor_);
	surface->Bar(
		x_ + borderWidth_, 
		y_ + borderWidth_, 
		x_ + width_ - borderWidth_, 
		y_ + height_ - borderWidth_, 
		color_
	);

	surface->Print(const_cast<char*>(text_.c_str()), x_, y_, 0x000000);
}