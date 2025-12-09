#include "sprite.hpp"

void Sprite::draw(Tmpl8::Surface* surface, float x, float y) {
	// no point in writing the same code if scaling by 1.0f has the same effect
	drawScaled(surface, x, y, 1.0f);
}

void Sprite::drawScaled(Tmpl8::Surface* surface, float x, float y, float scale) {
	sprite_->DrawScaled(
		static_cast<int>(x),
		static_cast<int>(y),
		static_cast<int>(getWidth() * scale),
		static_cast<int>(getHeight() * scale),
		surface
	);
}

void Sprite::setFrame(unsigned int index) { 
	// clamp index to existing frames
	index = std::min(index, maxFrames_);
	index = std::max(index, unsigned int(0));

	sprite_->SetFrame(index); 
}