#pragma once
#include "surface.h"
#include "object.hpp"
#include "mouseSignals.hpp"
#include <string>

class Button : public Object {
public:
	Button(
		std::function<void()> handler,
		std::string& text,
		int x = 0,
		int y = 0,
		int width = 10,
		int height = 10,
		int borderWidth = 1,
		Tmpl8::Pixel color = 0xffffff,
		Tmpl8::Pixel borderColor = 0x000000
	) :
		Object(x, y, BoundingBox(Tmpl8::vec2(0, 0), Tmpl8::vec2(width, height))),
		handler_(handler),
		text_(text),
		borderWidth_(borderWidth),
		color_(color),
		borderColor_(borderColor) 
	{
		mousePressed.subscribe([this](int x, int y) {
			BoundingBox absolutePosBounds = boundingBox_.at(Tmpl8::vec2(x_, y_));
			BoundingBox mouseBounds = BoundingBox(Tmpl8::vec2(x, y), Tmpl8::vec2(1, 1));

			if (absolutePosBounds.isInBounds(mouseBounds))
				active = true;
		});

		mouseReleased.subscribe([this]() {
			if (active)
				handler_();

			active = false;
		});
	};

	void draw(Tmpl8::Surface* surface) override;
	void process() override {}
private:
	std::function<void()> handler_;

	int borderWidth_;
	Tmpl8::Pixel color_;
	Tmpl8::Pixel borderColor_;
	std::string text_;

	bool active = false;
	bool hover = false;
};