#pragma once
#include "surface.h"
#include "object.hpp"
#include "vec2.hpp"
#include "text.hpp"
#include "clickable.hpp"
#include <functional>

class Button : public Object, public Clickable {
public:
	Button(
		int64_t id,
		std::function<void()> handler,
		const std::string& text,
		vec2<float> pos = vec2<float>(0.0f),
		vec2<float> size = vec2<float>(0.0f),
		int borderWidth = 1,
		Tmpl8::Pixel color = 0xffffffff,
		Tmpl8::Pixel borderColor = 0xff000000
	);

	void onMouseDown(vec2<float> pos, vec2<float> screenPos) override;

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	void process(float deltaTime) override {}
private:
	std::function<void()> handler_;
	int borderWidth_;
	Tmpl8::Pixel color_;
	Tmpl8::Pixel borderColor_;
	Text text_;
};