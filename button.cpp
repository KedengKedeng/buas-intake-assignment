#include "button.hpp"
#include "mouseSignals.hpp"
#include "boundingBox.hpp"

Button::Button(
	int64_t id,
	std::function<void()> handler,
	const std::string& text,
	vec2<float>& pos,
	vec2<float>& size,
	int borderWidth,
	Tmpl8::Pixel color,
	Tmpl8::Pixel borderColor
) :
	Object(id, pos, size),
	handler_(handler),
	text_(Text(const_cast<std::string&>(text), 1, 0xff000000)),
	borderWidth_(borderWidth),
	color_(color),
	borderColor_(borderColor)
{};

void Button::subscribe() {
	addSubscription(onMouseDown.subscribe([this](vec2<float>& pos) {
		BoundingBox absolutePosBounds(pos_, size_);

		if (absolutePosBounds.isInBounds(pos))
			active = true;
	}));

	addSubscription(onMouseUp.subscribe([this]() {
		if (active) handler_();

		active = false;
	}));
}

void Button::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	vec2 pos = pos_ + offset;
	surface->Bar(pos, pos + size_, borderColor_);
	surface->Bar(
		pos + borderWidth_,
		pos + size_ - borderWidth_,
		color_
	);

	float textLeft = pos.x + (size_.x - text_.getWidth()) / 2;
	float textTop = pos.y + (size_.y - text_.getHeight()) / 2;
	text_.draw(surface, vec2(textLeft, textTop));
}