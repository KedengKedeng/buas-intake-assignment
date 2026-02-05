#include "button.hpp"
#include "boundingBox.hpp"

Button::Button(
	int64_t id,
	std::function<void()> handler,
	const std::string& text,
	vec2<float> pos,
	vec2<float> size,
	int borderWidth,
	Tmpl8::Pixel color,
	Tmpl8::Pixel borderColor
) :
	Object(id, pos, size),
	Clickable(handler),
	text_(Text(const_cast<std::string&>(text), 1, 0xff000000)),
	borderWidth_(borderWidth),
	color_(color),
	borderColor_(borderColor)
{
	mouseHandler_.setInteractionCheck([this](vec2<float>& pos) {
		return BoundingBox(getPos(), getSize()).isInBounds(pos);
	});
};

void Button::subscribe() {
	mouseHandler_.subscribe();
	addSubscription([this]() {mouseHandler_.unsubscribe(); });
}

void Button::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	auto size = getSize();
	surface->Bar(pos, pos + size, borderColor_);
	surface->Bar(
		pos + borderWidth_,
		pos + size - borderWidth_,
		color_
	);

	text_.draw(surface, pos + (size - vec2<float>(text_.getWidth(), text_.getHeight())) / 2);
}