#include "tooltip.hpp"

Tooltip::Tooltip(int64_t id, const vec2<float>& pos, std::string& text) :
	Object(id, pos, vec2(0.0f)),
	text_(Text(text, 1, 0x00))
{
	setSize(vec2<float>(text_.getWidth(), text_.getHeight()) + 40);
}

void Tooltip::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto pos = getPos() + offset;
	surface->Bar(pos, pos + getSize(), 0xffffffff);
	text_.draw(surface, pos + 20);
}