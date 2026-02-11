#pragma once
#include "sprite.hpp"
#include <vector>


class SpriteSheet {
	using SpriteList = std::vector<Sprite>;
public:
	SpriteSheet(const SpriteList& sprites);
	SpriteSheet(std::shared_ptr<Tmpl8::Surface> surface, int columns, int rows);
	SpriteSheet(const Sprite& sprite);

	int getRows() const { return rows_; }
	int getColumns() const { return columns_; }
	int getSpriteCount() const { return static_cast<int>(sprites_.size()); }

	const Sprite& getSprite(int row, int column) const;
	const Sprite& getSprite(int index) const;

	float getWidth() const { return sprites_[0].getWidth(); }
	float getHeight() const { return sprites_[0].getHeight(); }

	SpriteList::iterator begin() { return sprites_.begin(); }
	SpriteList::iterator end() { return sprites_.end(); }
private:
	int rows_;
	int columns_;
	SpriteList sprites_;
};