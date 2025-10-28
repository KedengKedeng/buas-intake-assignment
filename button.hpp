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
		Tmpl8::vec2 pos = Tmpl8::vec2(0),
		Tmpl8::vec2 size = Tmpl8::vec2(0),
		int borderWidth = 1,
		Tmpl8::Pixel color = 0xffffff,
		Tmpl8::Pixel borderColor = 0x000000
	);

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