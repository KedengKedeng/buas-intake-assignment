// Template, BUAS version https://www.buas.nl/games
// IGAD/BUAS(NHTV)/UU - Jacco Bikker - 2006-2020

#pragma once
#include <string>
#include "vec2.hpp"
#include "template.h"

namespace Tmpl8 {

constexpr int RedMask = 0xff000000;
constexpr int GreenMask = 0x00ff0000;
constexpr int BlueMask = 0x0000ff00;
constexpr int AlphaMask = 0x000000ff;

typedef uint32_t Pixel;

inline Pixel blendAlpha(Pixel fg, Pixel bg) {
	uint32_t srcA = (fg >> 24) & 0xFF;
	uint32_t srcR = (fg >> 16) & 0xFF;
	uint32_t srcG = (fg >> 8) & 0xFF;
	uint32_t srcB = fg & 0xFF;

	uint32_t dstA = (bg >> 24) & 0xFF;
	uint32_t dstR = (bg >> 16) & 0xFF;
	uint32_t dstG = (bg >> 8) & 0xFF;
	uint32_t dstB = bg & 0xFF;

	uint32_t outA = srcA + dstA * (255 - srcA) / 255;

	uint32_t outR = (srcR * srcA + dstR * dstA * (255 - srcA) / 255) / 255;
	uint32_t outG = (srcG * srcA + dstG * dstA * (255 - srcA) / 255) / 255;
	uint32_t outB = (srcB * srcA + dstB * dstA * (255 - srcA) / 255) / 255;

	return (outA << 24) | (outR << 16) | (outG << 8) | outB;
}


inline Pixel AddBlend( Pixel a_Color1, Pixel a_Color2 )
{
	const unsigned int r = (a_Color1 & RedMask) + (a_Color2 & RedMask);
	const unsigned int g = (a_Color1 & GreenMask) + (a_Color2 & GreenMask);
	const unsigned int b = (a_Color1 & BlueMask) + (a_Color2 & BlueMask);
	const unsigned int a = (a_Color1 & AlphaMask) + (a_Color2 & AlphaMask);
	const unsigned r1 = (r & RedMask) | (RedMask * (r >> 24));
	const unsigned g1 = (g & GreenMask) | (GreenMask * (g >> 16));
	const unsigned b1 = (b & BlueMask) | (BlueMask * (b >> 8));
	const unsigned a1 = (a & AlphaMask) | (AlphaMask) * (a);
	return (r1 + g1 + b1 + a1);
}

// subtractive blending
inline Pixel SubBlend( Pixel a_Color1, Pixel a_Color2 )
{
	Pixel red = (a_Color1 & RedMask) - (a_Color2 & RedMask);
	Pixel green = (a_Color1 & GreenMask) - (a_Color2 & GreenMask);
	Pixel blue = (a_Color1 & BlueMask) - (a_Color2 & BlueMask);
	Pixel alpha = (a_Color1 & AlphaMask) - (a_Color2 & AlphaMask);
	return red + green + blue + alpha;
}

struct BoundsCheckResult {
	int x, y, x2, y2;
	bool dontPrint;
};

int LineOutCode(float x, float y, float xMin, float xMax, float yMin, float yMax);

class Surface
{
	enum { OWNER = 1 };
public:
	// constructor / destructor
	Surface( int a_Width, int a_Height, Pixel* a_Buffer, int a_Pitch );
	Surface( int a_Width, int a_Height );
	Surface( const std::string& a_File );
	~Surface();
	// member data access
	Pixel* GetBuffer() const { return m_Buffer; }
	void SetBuffer( Pixel* a_Buffer ) { m_Buffer = a_Buffer; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	int GetPitch() const { return m_Pitch; }
	void SetPitch( int a_Pitch ) { m_Pitch = a_Pitch; }

	// Special operations
	void Clear( Pixel a_Color );

	template<Arithmatic T>
	void Line(vec2<T> pos_, vec2<T> pos2_, Pixel color) {
		// clip (Cohen-Sutherland, https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm)
		// make sure given positions are converted to floats
		vec2<float> pos(pos_.x, pos_.y);
		vec2<float> pos2(pos2_.x, pos2_.y);

		const float xmin = 0, ymin = 0, xmax = static_cast<float>(m_Width - 1), ymax = static_cast<float>(m_Height - 1);
		int c0 = LineOutCode(pos.x, pos.y, xmin, xmax, ymin, ymax);
		int c1 = LineOutCode(pos2.x, pos2.y, xmin, xmax, ymin, ymax);
		bool accept = false;
		while (1)
		{
			if (!(c0 | c1)) { 
				accept = true; 
				break; 
			}
			else if (c0 & c1) break; 
			else {
				float x = 1.0f, y = 1.0f;
				const int co = c0 ? c0 : c1;
				if (co & 8) x = pos.x + (pos2.x - pos.x) * (ymax - pos.y) / (pos2.y - pos.y), y = ymax;
				else if (co & 4) x = pos.x + (pos2.x - pos.x) * (ymin - pos.y) / (pos2.y - pos.y), y = ymin;
				else if (co & 2) y = pos.y + (pos2.y - pos.y) * (xmax - pos.x) / (pos2.x - pos.x), x = xmax;
				else if (co & 1) y = pos.y + (pos2.y - pos.y) * (xmin - pos.x) / (pos2.x - pos.x), x = xmin;
				if (co == c0) pos.x = x, pos.y = y, c0 = LineOutCode(pos.x, pos.y, xmin, xmax, ymin, ymax);
				else pos2.x = x, pos2.y = y, c1 = LineOutCode(pos2.x, pos2.y, xmin, xmax, ymin, ymax);
			}
		}
		if (!accept) return;
		float b = pos2.x - pos.x;
		float h = pos2.y - pos.y;
		float l = fabsf(b);
		if (fabsf(h) > l) l = fabsf(h);
		int il = static_cast<int>(l);
		float dx = b / l;
		float dy = h / l;
		for (int i = 0; i <= il; i++)
		{
			int px = static_cast<int>(pos.x);
			int py = static_cast<int>(pos.y);
			if (px > 0 && px < m_Width && py > 0 && py < m_Height) *(m_Buffer + px + py * m_Pitch) = color;
			pos.x += dx, pos.y += dy;
		}
	}

	void Plot( int x, int y, Pixel c );
	void LoadImage( const char* a_File );
	void CopyTo( Surface& a_Dst, int a_X, int a_Y ) const;
	void BlendCopyTo( Surface& a_Dst, int a_X, int a_Y ) const;
	void ScaleColor( unsigned int a_Scale );

	template<Arithmatic T>
	void Box( vec2<T> pos, vec2<T> pos2, Pixel color ) {
		Line(pos, vec2(pos2.x, pos.y), color);
		Line(vec2(pos2.x, pos.y), pos2, color);
		Line(vec2(pos.x, pos2.y), pos2, color);
		Line(pos, vec2(pos.x, pos2.y), color);
	}

	template<Arithmatic T>
	void Bar(vec2<T> pos, vec2<T> pos2, Pixel color) {
		BoundsCheckResult result = checkBounds(
			static_cast<int>(floor(pos.x)),
			static_cast<int>(floor(pos.y)),
			static_cast<int>(floor(pos2.x)),
			static_cast<int>(floor(pos2.y)),
			GetWidth(),
			GetHeight()
		);

		if (result.dontPrint) return;

		Pixel* a = result.x + result.y * m_Pitch + m_Buffer;
		for (int y = result.y; y < result.y2; y++)
		{
			for (int x = 0; x < (result.x2 - result.x); x++) a[x] = blendAlpha(color, a[x]);
			a += m_Pitch;
		}
	}

	void Resize(const Surface& a_Orig );

	BoundsCheckResult checkBounds(int x1, int y1, int x2, int y2, int targetWidth, int targetHeight);
private:
	// Attributes
	Pixel* m_Buffer{nullptr};	
	int m_Width{0}, m_Height{0};
	int m_Pitch{0};
	int m_Flags{0};
};

}; // namespace Tmpl8