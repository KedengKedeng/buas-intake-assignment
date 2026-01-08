#pragma once
#include "sprite.hpp"
#include <vector>


class SpriteSheet {
	using SpriteList = std::vector<Sprite>;
public:
	SpriteSheet(const SpriteList& sprites);
	SpriteSheet(std::shared_ptr<Tmpl8::Surface> surface, int columns, int rows);

	int getRows() { return rows_; }
	int getColumns() { return columns_; }
	int getSpriteCount() { return sprites_.size(); }

	Sprite& getSprite(int row, int column);
	Sprite& getSprite(int index);

	float getWidth() { return sprites_[0].getWidth(); }
	float getHeight() { return sprites_[0].getHeight(); }

	SpriteList::iterator begin() { return sprites_.begin(); }
	SpriteList::iterator end() { return sprites_.end(); }
private:
	int rows_;
	int columns_;
	SpriteList sprites_;
};