#include "tooltip.hpp"

Tooltip::Tooltip(int64_t id, vec2<float>& pos, std::string& text) :
	Object(id, pos, vec2(0.0f)),
	text_(Text(text, 1, 0x00))
{
	setSize(vec2<float>(text_.getWidth(), text_.getHeight()) + 40);
}

void Tooltip::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Bar(
		static_cast<int>(pos_.x + offset.x),
		static_cast<int>(pos_.y + offset.y),
		static_cast<int>(pos_.x + size_.x + offset.x),
		static_cast<int>(pos_.y + size_.y + offset.y),
		0xffffff
	);

	text_.draw(surface, pos_ + offset + 20);
}