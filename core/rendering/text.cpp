#include "text.hpp"
#include "string.hpp"

char Text::s_Font[51][5][6];
bool Text::fontInitialized = false;
int Text::s_Transl[256];

Text::Text(std::string& text, int fontSize, Tmpl8::Pixel color) :
	text_(split(text, "\n")),
	fontSize_(fontSize),
	color_(color)
{
	if (!fontInitialized)
	{
		InitCharset();
		fontInitialized = true;
	}
}

int Text::getWidth() const { 
	size_t maxSize = 0;
	for (auto& text : text_) if (text.size() > maxSize) maxSize = text.size();
	return 6 * fontSize_ * static_cast<int>(maxSize); 
}

void Text::draw(Tmpl8::Surface& surface, vec2<float> pos) const
{
	int width = getWidth();
	int height = getHeight();

	int startX = static_cast<int>(floor(pos.x));
	int startY = static_cast<int>(floor(pos.y));

	auto result = surface.checkBounds(
		startX,
		startY,
		startX + width,
		startY + height,
		surface.GetWidth(),
		surface.GetHeight()
	);

	if (result.dontPrint) return;

	int pitch = surface.GetPitch();
	Tmpl8::Pixel* buffer = surface.GetBuffer();

	int penY = startY;

	for (auto& text : text_)
	{
		int offset = (width - getLineWidth(text)) / 2;
		int penX = startX + offset;

		for (int i = 0; i < static_cast<int>(text.size()); i++, penX += 6 * fontSize_)
		{
			char currentChar = text[i];
			long glyphIndex = 0;

			if ((currentChar >= 'A') && (currentChar <= 'Z'))
				glyphIndex = s_Transl[(unsigned short)(currentChar - ('A' - 'a'))];
			else
				glyphIndex = s_Transl[(unsigned short)currentChar];

			char* glyphBitmap = reinterpret_cast<char*>(s_Font[glyphIndex]);

			for (int glyphRow = 0; glyphRow < 5; glyphRow++, glyphBitmap++)
			{
				for (int row = 0; row < fontSize_; row++)
				{
					int y = penY + glyphRow * fontSize_ + row;
					if (y < result.y || y >= result.y2) continue;

					for (int glyphColumn = 0; glyphColumn < 5; glyphColumn++)
					{
						for (int column = 0; column < fontSize_; column++)
						{
							int x = penX + glyphColumn * fontSize_ + column;
							if (x < result.x || x >= result.x2) continue;

							if (*glyphBitmap == 'o')
							{
								buffer[x + y * pitch] = color_;
								// not needed but makes it look a bit nicer
								if (y + 1 < result.y2)
									buffer[x + (y + 1) * pitch] = color_;
							}
						}
						glyphBitmap++;
					}
					// reset bitmap to start of the characters 
					glyphBitmap -= 5;
				}
				// go to the next character
				glyphBitmap += 5;
			}
		}
		// advance to next column
		penY += 6 * fontSize_;
	}
}


void Text::SetChar(int c, char* c1, char* c2, char* c3, char* c4, char* c5)
{
	strcpy(s_Font[c][0], c1);
	strcpy(s_Font[c][1], c2);
	strcpy(s_Font[c][2], c3);
	strcpy(s_Font[c][3], c4);
	strcpy(s_Font[c][4], c5);
}

void Text::InitCharset()
{
	SetChar(0, ":ooo:", "o:::o", "ooooo", "o:::o", "o:::o");
	SetChar(1, "oooo:", "o:::o", "oooo:", "o:::o", "oooo:");
	SetChar(2, ":oooo", "o::::", "o::::", "o::::", ":oooo");
	SetChar(3, "oooo:", "o:::o", "o:::o", "o:::o", "oooo:");
	SetChar(4, "ooooo", "o::::", "oooo:", "o::::", "ooooo");
	SetChar(5, "ooooo", "o::::", "ooo::", "o::::", "o::::");
	SetChar(6, ":oooo", "o::::", "o:ooo", "o:::o", ":ooo:");
	SetChar(7, "o:::o", "o:::o", "ooooo", "o:::o", "o:::o");
	SetChar(8, "::o::", "::o::", "::o::", "::o::", "::o::");
	SetChar(9, ":::o:", ":::o:", ":::o:", ":::o:", "ooo::");
	SetChar(10, "o::o:", "o:o::", "oo:::", "o:o::", "o::o:");
	SetChar(11, "o::::", "o::::", "o::::", "o::::", "ooooo");
	SetChar(12, "oo:o:", "o:o:o", "o:o:o", "o:::o", "o:::o");
	SetChar(13, "o:::o", "oo::o", "o:o:o", "o::oo", "o:::o");
	SetChar(14, ":ooo:", "o:::o", "o:::o", "o:::o", ":ooo:");
	SetChar(15, "oooo:", "o:::o", "oooo:", "o::::", "o::::");
	SetChar(16, ":ooo:", "o:::o", "o:::o", "o::oo", ":oooo");
	SetChar(17, "oooo:", "o:::o", "oooo:", "o:o::", "o::o:");
	SetChar(18, ":oooo", "o::::", ":ooo:", "::::o", "oooo:");
	SetChar(19, "ooooo", "::o::", "::o::", "::o::", "::o::");
	SetChar(20, "o:::o", "o:::o", "o:::o", "o:::o", ":oooo");
	SetChar(21, "o:::o", "o:::o", ":o:o:", ":o:o:", "::o::");
	SetChar(22, "o:::o", "o:::o", "o:o:o", "o:o:o", ":o:o:");
	SetChar(23, "o:::o", ":o:o:", "::o::", ":o:o:", "o:::o");
	SetChar(24, "o:::o", "o:::o", ":oooo", "::::o", ":ooo:");
	SetChar(25, "ooooo", ":::o:", "::o::", ":o:::", "ooooo");
	SetChar(26, ":ooo:", "o::oo", "o:o:o", "oo::o", ":ooo:");
	SetChar(27, "::o::", ":oo::", "::o::", "::o::", ":ooo:");
	SetChar(28, ":ooo:", "o:::o", "::oo:", ":o:::", "ooooo");
	SetChar(29, "oooo:", "::::o", "::oo:", "::::o", "oooo:");
	SetChar(30, "o::::", "o::o:", "ooooo", ":::o:", ":::o:");
	SetChar(31, "ooooo", "o::::", "oooo:", "::::o", "oooo:");
	SetChar(32, ":oooo", "o::::", "oooo:", "o:::o", ":ooo:");
	SetChar(33, "ooooo", "::::o", ":::o:", "::o::", "::o::");
	SetChar(34, ":ooo:", "o:::o", ":ooo:", "o:::o", ":ooo:");
	SetChar(35, ":ooo:", "o:::o", ":oooo", "::::o", ":ooo:");
	SetChar(36, "::o::", "::o::", "::o::", ":::::", "::o::");
	SetChar(37, ":ooo:", "::::o", ":::o:", ":::::", "::o::");
	SetChar(38, ":::::", ":::::", "::o::", ":::::", "::o::");
	SetChar(39, ":::::", ":::::", ":ooo:", ":::::", ":ooo:");
	SetChar(40, ":::::", ":::::", ":::::", ":::o:", "::o::");
	SetChar(41, ":::::", ":::::", ":::::", ":::::", "::o::");
	SetChar(42, ":::::", ":::::", ":ooo:", ":::::", ":::::");
	SetChar(43, ":::o:", "::o::", "::o::", "::o::", ":::o:");
	SetChar(44, "::o::", ":::o:", ":::o:", ":::o:", "::o::");
	SetChar(45, ":::::", ":::::", ":::::", ":::::", ":::::");
	SetChar(46, "ooooo", "ooooo", "ooooo", "ooooo", "ooooo");
	SetChar(47, "::o::", "::o::", ":::::", ":::::", ":::::"); // Tnx Ferry
	SetChar(48, "o:o:o", ":ooo:", "ooooo", ":ooo:", "o:o:o");
	SetChar(49, "::::o", ":::o:", "::o::", ":o:::", "o::::");
	char c[] = "abcdefghijklmnopqrstuvwxyz0123456789!?:=,.-() #'*/";
	int i;
	for (i = 0; i < 256; i++) s_Transl[i] = 45;
	for (i = 0; i < 50; i++) s_Transl[(unsigned char)c[i]] = i;
}