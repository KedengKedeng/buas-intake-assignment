#pragma once
#include <map>
#include <string>
#include <memory>
#include "sprite.hpp"
#include "animatedSprite.hpp"

class SpriteRepository {
public:
	void insert(const std::string& name, Sprite& sprite) { registry_.insert({ name, std::move(sprite) }); }
	void insertAnimated(const std::string& name, AnimatedSprite& sprite) { animatedRegistry_.insert({ name, std::move(sprite) }); }
	Sprite get(const std::string& name, float scale = 1.0f) { return Sprite(registry_.at(name), scale); }
	AnimatedSprite getAnimated(const std::string& name, float frameRate, float scale = 1.0f) { return AnimatedSprite(animatedRegistry_.at(name), frameRate, scale); }
private:
	std::map<std::string, Sprite> registry_ = {};
	std::map<std::string, AnimatedSprite> animatedRegistry_ = {};
};

extern SpriteRepository spriteRepository;
