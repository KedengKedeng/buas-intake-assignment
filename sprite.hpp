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
	Sprite(const Sprite& other, float scale);

	void draw(Tmpl8::Surface* surface, float x, float y) const;
	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale) const;
	void drawScaled(Tmpl8::Surface* target, float x, float y, float width, float height) const;

	void setFlags(unsigned int flags) { flags_ = flags; }
	unsigned int getFlags() const { return flags_; }

	// returns scaled sizes
	float getWidth() const { return rect_.width * scale_; }
	float getHeight() const { return rect_.height * scale_; }

	Tmpl8::Pixel* getBuffer() const { return surface_->GetBuffer(); }
	std::shared_ptr<Tmpl8::Surface> getSurface() const { return surface_; }
private:
	int pitch_;
	Rect2<int> rect_;
	float scale_;
	unsigned int flags_;

	const std::shared_ptr<Tmpl8::Surface> surface_;
};