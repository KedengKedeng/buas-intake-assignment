#pragma once
#include <map>
#include <string>
#include <memory>
#include "sprite.hpp"
#include "spritesheet.hpp"

class SpriteRepository {
public:
	void insert(const std::string& name, Sprite& sprite) { registry_.insert({ name, std::move(sprite) }); }
	void insertSheet(const std::string& name, SpriteSheet& sheet) { sheetRegistry_.insert({ name, std::make_shared<SpriteSheet>(std::move(sheet)) }); }
	Sprite get(const std::string& name, float scale = 1.0f) { return Sprite(registry_.at(name), scale); }
	std::shared_ptr<SpriteSheet> getSheet(const std::string& name) { return sheetRegistry_.at(name); }
private:
	std::map<std::string, Sprite> registry_ = {};
	std::map<std::string, std::shared_ptr<SpriteSheet>> sheetRegistry_ = {};
};

extern SpriteRepository spriteRepository;
