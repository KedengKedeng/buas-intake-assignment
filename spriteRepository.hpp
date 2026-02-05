#pragma once
#include <map>
#include <string>
#include <memory>
#include "sprite.hpp"
#include "spritesheet.hpp"

enum class Sprites {
	WaterBottle,
	Spoon,

	EmptyCauldron,
	CauldronCloseupFront,
	CauldronCloseupBack
};

enum class SpriteSheets {
	PlayerIdleLeft,
	PlayerIdleRight,
	PlayerWalkLeft,
	PlayerWalkRight,

	BlueSlimeIdleLeft,
	BlueSlimeIdleRight,
	BlueSlimeWalkLeft,
	BlueSlimeWalkRight,

	EmptyBurningCauldron,
	FilledCauldron,
	FilledBurningCauldron,
	CauldronCloseupFire,
	CauldronCloseupFilled,

	Blower,
	Floor
};

class SpriteRepository {
public:
	SpriteRepository();

	void insert(Sprites name, Sprite& sprite) { registry_.insert({ name, std::move(sprite) }); }
	void insertSheet(SpriteSheets name, SpriteSheet& sheet) { sheetRegistry_.insert({ name, std::make_shared<SpriteSheet>(std::move(sheet)) }); }
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
