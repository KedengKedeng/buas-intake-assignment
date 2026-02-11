#include "sprite.hpp"

Sprite::Sprite(std::shared_ptr<Tmpl8::Surface> surface, Rect2<int> rect, float scale) :
	pitch_(surface->GetWidth()),
	rect_(rect),
	scale_(scale),
	flags_(0),
	surface_(surface)
{}

Sprite::Sprite(std::shared_ptr<Tmpl8::Surface> surface, float scale) :
	pitch_(surface->GetWidth()),
	rect_(Rect2<int>(0, 0, surface->GetWidth(), surface->GetHeight())),
	scale_(scale),
	flags_(0),
	surface_(surface)
{}

Sprite::Sprite(const Sprite& other, float scale):
	pitch_(other.pitch_),
	rect_(other.rect_),
	scale_(scale),
	flags_(other.flags_),
	surface_(other.surface_) 
{}

void Sprite::draw(Tmpl8::Surface& target, float x, float y) const
{
	drawScaled(target, x, y, 1.0f);
}

// keeps aspect ratio
void Sprite::drawScaled(Tmpl8::Surface& target, float x, float y, float scale) const
{
	drawScaled(target, x, y, getWidth() * scale, getHeight() * scale);
}

// scales into any size
void Sprite::drawScaled(Tmpl8::Surface& target, float x, float y, float width, float height) const
{
	if (width == 0 || height == 0) return;

	// convert everything explicitly to ints via ceil and floor to avoid out of bounds errors
	int x1 = static_cast<int>(ceil(x));
	int y1 = static_cast<int>(ceil(y));
	int x2 = static_cast<int>(floor(x + width));
	int y2 = static_cast<int>(floor(y + height));

	Tmpl8::BoundsCheckResult result = target.checkBounds(x1, y1, x2, y2, target.GetWidth(), target.GetHeight());
	if (result.dontPrint) return;

	Tmpl8::Pixel* spriteBuffer = getBuffer();

	Tmpl8::Pixel* targetBuffer = target.GetBuffer();
	int targetPitch = target.GetPitch();

	for (int ty = result.y; ty < result.y2; ty++)
	{
		int v = static_cast<int>(floor(rect_.y + ((ty - y) / height) * rect_.height));

		for (int tx = result.x; tx < result.x2; tx++)
		{
			int u = static_cast<int>(floor(rect_.x + ((tx - x) / width) * rect_.width));

			Tmpl8::Pixel src = spriteBuffer[u + v * pitch_];
			unsigned int srcA = (src >> 24) & 0xFF;

			if (srcA == 0) continue;

			Tmpl8::Pixel dst = targetBuffer[tx + ty * targetPitch];

			targetBuffer[tx + ty * targetPitch] = Tmpl8::blendAlpha(src, dst);
		}
	}
}