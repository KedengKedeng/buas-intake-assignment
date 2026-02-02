#include "textureTooltip.hpp"

TextureTooltip::TextureTooltip(int64_t id, const vec2<float>& pos, AnimatedSprite& sprite) :
	Object(id, pos, vec2(0.0f)),
	sprite_(sprite)
{
	setSize(vec2<float>(sprite_.getWidth(), sprite_.getHeight()) + 40);
}

void TextureTooltip::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Bar(
		pos_ + offset,
		pos_ + size_ + offset,
		0xffffffff
	);

	sprite_.draw(surface, pos_.x + offset.x + 20, pos_.y + offset.y + 20);
}

void TextureTooltip::process(float deltaTime) {
	sprite_.process(deltaTime);
}