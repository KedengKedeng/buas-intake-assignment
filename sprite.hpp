#pragma once
#include "surface.h"
#include "rect2.hpp"
#include <memory>

class Sprite
{
public:
	// Sprite flags
	enum
	{
		FLARE = (1 << 0),
		OPFLARE = (1 << 1),
		FLASH = (1 << 4),
		DISABLED = (1 << 6),
		GMUL = (1 << 7),
		BLACKFLARE = (1 << 8),
		BRIGHTEST = (1 << 9),
		RFLARE = (1 << 12),
		GFLARE = (1 << 13),
		NOCLIP = (1 << 14)
	};

	Sprite(std::shared_ptr<Tmpl8::Surface> a_Surface, Rect2<int> rect, float scale = 1.0f);
	Sprite(std::shared_ptr<Tmpl8::Surface> a_Surface, float scale = 1.0f);
	Sprite(Sprite& other, float scale);

	void draw(Tmpl8::Surface* surface, float x, float y);
	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale);
	void drawScaled(Tmpl8::Surface* target, float x, float y, float width, float height);

	void setFlags(unsigned int flags) { flags_ = flags; }
	unsigned int getFlags() const { return flags_; }

	// returns scaled sizes
	float getWidth() { return rect_.width * scale_; }
	float getHeight() { return rect_.height * scale_; }

	Tmpl8::Pixel* getBuffer() { return surface_->GetBuffer(); }
	std::shared_ptr<Tmpl8::Surface> getSurface() { return surface_; }
private:
	int pitch_;
	Rect2<int> rect_;
	float scale_;
	unsigned int flags_;

	std::shared_ptr<Tmpl8::Surface> surface_;
};