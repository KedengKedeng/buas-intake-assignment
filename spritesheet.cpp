#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(const SpriteList& sprites) :
	sprites_(sprites),
	rows_(static_cast<int>(sprites_.size())),
	columns_(1)
{}

SpriteSheet::SpriteSheet(std::shared_ptr<Tmpl8::Surface> surface, int columns, int rows) :
	sprites_({}),
	columns_(columns),
	rows_(rows)
{
	sprites_.reserve(columns * rows);

	int spriteWidth = surface->GetWidth() / rows;
	int spriteHeight = surface->GetHeight() / columns;

	int currentXPos = 0;
	for (int x = 0; x < rows; x++) {
		int currentYPos = 0;
		for (int y = 0; y < columns; y++) {
			sprites_.emplace_back(Sprite(surface, Rect2<int>(currentXPos, currentYPos, spriteWidth, spriteHeight)));
			currentYPos += spriteHeight;
		}
		currentXPos += spriteWidth;
	}
}

const Sprite& SpriteSheet::getSprite(int row, int column) const {
	return sprites_.at(row * column);
}

const Sprite& SpriteSheet::getSprite(int index) const {
	return sprites_.at(index);
}