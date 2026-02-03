#include "textureTooltip.hpp"

TextureTooltip::TextureTooltip(int64_t id, const vec2<float>& pos, AnimatedSprite& sprite) :
	Object(id, pos, vec2(0.0f)),
	sprite_(sprite)
{
	setSize(vec2<float>(sprite_.getWidth(), sprite_.getHeight()) + 40);
}

void TextureTooltip::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto pos = getPos() + offset;
	surface->Bar(pos, pos + getSize(), 0xffffffff);
	sprite_.draw(surface, pos.x + 20, pos.y + 20);
}

void TextureTooltip::process(float deltaTime) {
	sprite_.process(deltaTime);
}