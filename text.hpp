#pragma once
#include <string>
#include "vec2.hpp"
#include "surface.h"

class Text {
public:
	Text(std::string& text, int fontScale, Tmpl8::Pixel color);

	int getWidth() { return (1 + 5) * fontSize_ * static_cast<int>(text_.size()); }
	int getHeight() { return 5 * fontSize_; }

	void draw(Tmpl8::Surface*, vec2<float>& pos);
private:
	std::string text_;
	int fontSize_;
	Tmpl8::Pixel color_;

	static char s_Font[51][5][6];
	static bool fontInitialized;
	static int s_Transl[256];

	void InitCharset();
	void SetChar(int c, char* c1, char* c2, char* c3, char* c4, char* c5);
};