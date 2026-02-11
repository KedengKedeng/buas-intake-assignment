#pragma once
#include "spritesheet.hpp"
#include "random.hpp"
#include <map>

template<typename TilemapType>
class Tilemap {
public:
	Tilemap(std::shared_ptr<SpriteSheet> sheet, float scale = 1.0f) :
		spriteSheet_(sheet),
		scale_(scale),
		tileSize_(vec2(sheet->getWidth(), sheet->getHeight()) * scale)
	{}

	void setTile(vec2<int> pos, TilemapType tile) { tiles_[pos] = tile; }

	// set a square within the tilemap where each tile is randomly picked from the given set
	void setSquare(const Rect2<int>& rect, const std::vector<TilemapType>& tiles){
		float posX = rect.x * tileSize_.x;
		for (int x = 0; x < rect.width; x++) {
			float posY = rect.y * tileSize_.y;
			for (int y = 0; y < rect.height; y++) {
				int64_t randomNum = getRandomNum();
				setTile(vec2<int>(posX, posY), tiles[randomNum % tiles.size()]);
				posY += tileSize_.y;
			}
			posX += tileSize_.x;
		}
	}

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const {
		for (auto& [pos, tile] : tiles_) {
			Sprite sprite = spriteSheet_->getSprite(static_cast<int>(tile));
			sprite.drawScaled(surface, pos.x + offset.x, pos.y + offset.y, scale_);
		}
	}
private:
	float scale_;

	vec2<float> tileSize_;

	std::shared_ptr<SpriteSheet> spriteSheet_;
	std::map<vec2<int>, TilemapType> tiles_ = {};
};