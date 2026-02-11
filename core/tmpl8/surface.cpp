// Template, BUAS version https://www.buas.nl/games
// IGAD/BUAS(NHTV)/UU - Jacco Bikker - 2006-2020

#include "surface.h"
#include <cassert>
#include <cstring>
#include "FreeImage.h"

namespace Tmpl8 {

void NotifyUser( char* s );

// -----------------------------------------------------------
// True-color surface class implementation
// -----------------------------------------------------------

BoundsCheckResult Surface::checkBounds(int x1, int y1, int x2, int y2, int targetWidth, int targetHeight) {
	x1 = std::max(x1, 0);
	y1 = std::max(y1, 0);
	x2 = std::min(x2, targetWidth);
	y2 = std::min(y2, targetHeight);

	if (x1 >= x2 || y1 >= y2) return {0,0,0,0,true};
	return { x1, y1, x2, y2, false };
}

Surface::Surface( int a_Width, int a_Height, Pixel* a_Buffer, int a_Pitch ) :
	m_Buffer( a_Buffer ),
	m_Width( a_Width ),
	m_Height( a_Height ),
	m_Pitch( a_Pitch )
{
}

Surface::Surface( int a_Width, int a_Height ) :
	m_Width( a_Width ),
	m_Height( a_Height ),
	m_Pitch( a_Width ),
	m_Flags(OWNER)
{
	m_Buffer = static_cast<Pixel*>(MALLOC64( (unsigned int)a_Width * (unsigned int)a_Height * sizeof( Pixel )));
}

Surface::Surface( const std::string& a_File )
{
	FILE* f = fopen( a_File.c_str(), "rb");
	if (!f) 
	{
		char t[128];
		sprintf( t, "File not found: %s", a_File.c_str() );
		NotifyUser( t ); 
		return;
	}
	else fclose( f );
	LoadImage( a_File.c_str() );
}

void Surface::LoadImage( const char* a_File )
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType( a_File, 0 );
	if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename( a_File );
	FIBITMAP* tmp = FreeImage_Load( fif, a_File );
	FIBITMAP* dib = FreeImage_ConvertTo32Bits( tmp );
	FreeImage_Unload( tmp );
	m_Width = m_Pitch = FreeImage_GetWidth( dib );
	m_Height = FreeImage_GetHeight( dib );
	m_Buffer = (Pixel*)MALLOC64( m_Width * m_Height * sizeof( Pixel ) );
    if (m_Buffer)
    {
        m_Flags = OWNER;
        assert(m_Pitch != 0);
        for (int y = 0; y < m_Height; y++)
        {
            if (m_Pitch != 0)
            {
                unsigned char* line = FreeImage_GetScanLine(dib, m_Height - 1 - y);
                memcpy( m_Buffer + (y * m_Pitch), line, m_Width * sizeof( Pixel ) );
            }
        }
    }
	FreeImage_Unload( dib );
}

Surface::~Surface()
{
	if (m_Flags & OWNER) 
	{
		// only delete if the buffer was not passed to us
		FREE64( m_Buffer );
	}
}

void Surface::Clear( Pixel a_Color )
{
	int s = m_Width * m_Height;
	for ( int i = 0; i < s; i++ ) m_Buffer[i] = a_Color;
}

void Surface::Resize( const Surface& a_Orig )
{
	Pixel* src = a_Orig.GetBuffer(), *dst = m_Buffer;
	int u, v, owidth = a_Orig.GetWidth(), oheight = a_Orig.GetHeight();
	int dx = (owidth << 10) / m_Width, dy = (oheight << 10) / m_Height;
	for ( v = 0; v < m_Height; v++ )
	{
		for ( u = 0; u < m_Width; u++ )
		{
			int su = u * dx, sv = v * dy;
			Pixel* s = src + (su >> 10) + (sv >> 10) * owidth;
			int ufrac = su & 1023, vfrac = sv & 1023;
			int w4 = (ufrac * vfrac) >> 12;
			int w3 = ((1023 - ufrac) * vfrac) >> 12;
			int w2 = (ufrac * (1023 - vfrac)) >> 12;
			int w1 = ((1023 - ufrac) * (1023 - vfrac)) >> 12;
			int x2 = ((su + dx) > ((owidth - 1) << 10))?0:1;
			int y2 = ((sv + dy) > ((oheight - 1) << 10))?0:1;
			Pixel p1 = *s, p2 = *(s + x2), p3 = *(s + owidth * y2), p4 = *(s + owidth * y2 + x2);
			unsigned int r = (((p1 & RedMask) * w1 + (p2 & RedMask) * w2 + (p3 & RedMask) * w3 + (p4 & RedMask) * w4) >> 8) & RedMask;
			unsigned int g = (((p1 & GreenMask) * w1 + (p2 & GreenMask) * w2 + (p3 & GreenMask) * w3 + (p4 & GreenMask) * w4) >> 8) & GreenMask;
			unsigned int b = (((p1 & BlueMask) * w1 + (p2 & BlueMask) * w2 + (p3 & BlueMask) * w3 + (p4 & BlueMask) * w4) >> 8) & BlueMask;
			unsigned int a = (((p1 & AlphaMask) * w1 + (p2 & AlphaMask) * w2 + (p3 & AlphaMask) * w3 + (p4 & AlphaMask) * w4) >> 8) & AlphaMask;
			*(dst + u + v * m_Pitch) = (Pixel)(r + g + b + a);
		}
	}
}

int LineOutCode(float x, float y, float xMin, float xMax, float yMin, float yMax)
{
	return (
		(x < xMin) ? 1 : ((x > xMax) ? 2 : 0)
	) + (
		(y < yMin) ? 4 : ((y > yMax) ? 8 : 0)
	);
}

void Surface::Plot( int x, int y, Pixel c )
{ 
	if ((x >= 0) && (y >= 0) && (x < m_Width) && (y < m_Height)) m_Buffer[x + y * m_Pitch] = c;
}

void Surface::CopyTo( Surface& a_Dst, int a_X, int a_Y ) const
{
	Pixel* dst = a_Dst.GetBuffer();
	Pixel* src = m_Buffer;
	if ((src) && (dst)) 
	{
		int srcwidth = m_Width;
		int srcheight = m_Height;
		int srcpitch = m_Pitch;
		int dstwidth = a_Dst.GetWidth();
		int dstheight = a_Dst.GetHeight();
		int dstpitch = a_Dst.GetPitch();
		if ((srcwidth + a_X) > dstwidth) srcwidth = dstwidth - a_X;
		if ((srcheight + a_Y) > dstheight) srcheight = dstheight - a_Y;
		if (a_X < 0) src -= a_X, srcwidth += a_X, a_X =0;
		if (a_Y < 0) src -= a_Y * srcpitch, srcheight += a_Y, a_Y = 0;
		if ((srcwidth > 0) && (srcheight > 0))
		{
			dst += a_X + dstpitch * a_Y;
			for ( int y = 0; y < srcheight; y++ )
			{
				memcpy( dst, src, srcwidth * 4 );
				dst += dstpitch;
				src += srcpitch;
			}
		}
	}
}

void Surface::BlendCopyTo(Surface& a_Dst, int a_X, int a_Y) const
{
	if (!m_Buffer || !a_Dst.GetBuffer())
		return;

	Pixel* dst = a_Dst.GetBuffer();
	Pixel* src = m_Buffer;

	int srcWidth = m_Width;
	int srcHeight = m_Height;
	int srcPitch = m_Pitch;
	int dstWidth = a_Dst.GetWidth();
	int dstHeight = a_Dst.GetHeight();
	int dstPitch = a_Dst.GetPitch();

	if (a_X < 0) { src += -a_X; srcWidth += a_X; a_X = 0; }
	if (a_Y < 0) { src += (-a_Y) * srcPitch; srcHeight += a_Y; a_Y = 0; }

	if ((a_X + srcWidth) > dstWidth)  srcWidth = dstWidth - a_X;
	if ((a_Y + srcHeight) > dstHeight) srcHeight = dstHeight - a_Y;

	if (srcWidth <= 0 || srcHeight <= 0)
		return;

	dst += a_X + a_Y * dstPitch;

	for (int y = 0; y < srcHeight; ++y)
	{
		for (int x = 0; x < srcWidth; ++x)
		{
			dst[x] = blendAlpha(src[x], dst[x]);
		}
		src += srcPitch;
		dst += dstPitch;
	}
}

void Surface::ScaleColor( unsigned int a_Scale )
{
	int s = m_Pitch * m_Height;
	for ( int i = 0; i < s; i++ )
	{
		Pixel c = m_Buffer[i];
		unsigned int rb = (((c & (RedMask|BlueMask)) * a_Scale) >> 5) & (RedMask|BlueMask);
		unsigned int g = (((c & GreenMask) * a_Scale) >> 5) & GreenMask;
		m_Buffer[i] = rb + g;
	}
}

}; // namespace Tmpl8