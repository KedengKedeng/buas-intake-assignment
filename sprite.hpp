#pragma once
#include "surface.h"
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

	// Structors
	Sprite(std::shared_ptr<Tmpl8::Surface> a_Surface, unsigned int a_NumFrames, float scale = 1.0f);
	Sprite(Sprite& other, float scale);

	// Methods
	void draw(Tmpl8::Surface* surface, float x, float y);
	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale);
	void drawScaled(Tmpl8::Surface* a_Target, float a_X, float a_Y, float a_Width, float a_Height);

	void setFrame(unsigned int a_Index);
	unsigned int getFrames() { return m_NumFrames; }

	void setFlags(unsigned int a_Flags) { m_Flags = a_Flags; }
	unsigned int getFlags() const { return m_Flags; }

	float getWidth() { return m_Width * scale_; }
	float getHeight() { return m_Height * scale_; }

	Tmpl8::Pixel* getBuffer() { return m_Surface->GetBuffer(); }
	std::shared_ptr<Tmpl8::Surface> getSurface() { return m_Surface; }
private:
	// Attributes
	int m_Width, m_Height, m_Pitch;
	float scale_;
	unsigned int m_NumFrames;
	unsigned int m_CurrentFrame;
	unsigned int m_Flags;
	std::shared_ptr<Tmpl8::Surface> m_Surface;
};