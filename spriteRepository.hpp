#pragma once
#include <map>
#include <memory>
#include "sprite.hpp"
#include "spritesheet.hpp"
#include "sprites.hpp"

class SpriteRepository {
public:
	SpriteRepository();

	void insert(Sprites name, Sprite& sprite) { registry_.insert({ name, std::move(sprite) }); }
	void insertSheet(SpriteSheets name, SpriteSheet& sheet) { sheetRegistry_.insert({ name, std::make_shared<SpriteSheet>(sheet) }); }
	Sprite get(Sprites name, float scale = 1.0f) { return Sprite(registry_.at(name), scale); }
	std::shared_ptr<SpriteSheet> getSheet(SpriteSheets name) { return sheetRegistry_.at(name); }
private:
	std::map<Sprites, Sprite> registry_ = {};
	std::map<SpriteSheets, std::shared_ptr<SpriteSheet>> sheetRegistry_ = {};
};

static SpriteRepository& spriteRepository() {
	static SpriteRepository repo;
	return repo;
}
