#include "sprite.hpp"

Sprite::Sprite(std::shared_ptr<Tmpl8::Surface> a_Surface, unsigned int a_NumFrames, float scale) :
	m_Width(static_cast<int>(a_Surface->GetWidth() / a_NumFrames)),
	m_Height(a_Surface->GetHeight()),
	m_Pitch(a_Surface->GetWidth()),
	scale_(scale),
	m_NumFrames(a_NumFrames),
	m_CurrentFrame(0),
	m_Flags(0),
	m_Surface(a_Surface)
{}

Sprite::Sprite(Sprite& other, float scale):
	m_Width(other.m_Width),
	m_Height(other.m_Height),
	m_Pitch(other.m_Pitch),
	scale_(scale),
	m_NumFrames(other.m_NumFrames),
	m_CurrentFrame(other.m_CurrentFrame),
	m_Flags(other.m_Flags),
	m_Surface(other.m_Surface) 
{}

void Sprite::draw(Tmpl8::Surface* a_Target, float a_X, float a_Y)
{
	drawScaled(a_Target, a_X, a_Y, 1.0f);
}

void Sprite::drawScaled(Tmpl8::Surface* a_Target, float a_X, float a_Y, float scale)
{
	drawScaled(a_Target, a_X, a_Y, getWidth() * scale, getHeight() * scale);
}

void Sprite::drawScaled(Tmpl8::Surface* a_Target, float a_X, float a_Y, float a_Width, float a_Height)
{
	int x1 = static_cast<int>(ceil(a_X));
	int y1 = static_cast<int>(ceil(a_Y));
	int x2 = static_cast<int>(floor(a_X + a_Width));
	int y2 = static_cast<int>(floor(a_Y + a_Height));

	if (a_Target->checkBounds(x1, y1, x2, y2, a_Target->GetWidth(), a_Target->GetHeight()).dontPrint) return;

	Tmpl8::Pixel* spriteBuffer = getBuffer() + m_CurrentFrame * m_Width;

	Tmpl8::Pixel* targetBuffer = a_Target->GetBuffer();
	int targetPitch = a_Target->GetPitch();

	for (int ty = y1; ty < y2; ty++)
	{
		float v = (ty - a_Y) / a_Height;
		int sy = static_cast<int>(v * m_Height);

		for (int tx = x1; tx < x2; tx++)
		{
			float u = (tx - a_X) / a_Width;
			int sx = static_cast<int>(u * m_Width);

			Tmpl8::Pixel color = spriteBuffer[sx + sy * m_Pitch];

			if (color) targetBuffer[tx + ty * targetPitch] = color;
		}
	}
}

void Sprite::setFrame(unsigned int a_Index) {
	// clamp index to existing frames
	a_Index = std::min(a_Index, m_NumFrames);
	a_Index = std::max(a_Index, unsigned int(0));

	m_CurrentFrame = a_Index;
}