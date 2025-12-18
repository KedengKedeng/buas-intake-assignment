#pragma once
#include <map>
#include <string>
#include <memory>
#include "sprite.hpp"

class SpriteRepository {
public:
	void insert(const std::string& name, Sprite& sprite) { registry_.insert({ name, std::move(sprite) }); }
	Sprite get(const std::string& name, float scale = 1.0f) { return Sprite(registry_.at(name), scale); }
private:
	std::map<std::string, Sprite> registry_ = {};
};

extern SpriteRepository spriteRepository;
