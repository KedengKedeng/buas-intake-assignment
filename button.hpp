#pragma once
#include "surface.h"
#include <string>

class Button {
	int x_;
	int y_;
	int width_;
	int height_;
	int borderWidth_;
	Tmpl8::Pixel color_;
	Tmpl8::Pixel borderColor_;
	std::string text_;

	bool active = false;
	bool hover = false;
public:
	Button(
		std::string& text,
		int x = 0,
		int y = 0,
		int width = 10,
		int height = 10,
		int borderWidth = 1,
		Tmpl8::Pixel color = 0xffffff,
		Tmpl8::Pixel borderColor = 0x000000
	) :
		text_(text),
		x_(x),
		y_(y),
		width_(width),
		height_(height),
		borderWidth_(borderWidth),
		color_(color),
		borderColor_(borderColor) {};

	void draw(Tmpl8::Surface* surface);
};