#pragma once
#include <map>
#include <string>
#include <memory>
#include "surface.h"

class SpriteRepository {
public:
	void insert(const std::string& name, std::shared_ptr<Tmpl8::Sprite> sprite) { registry_.insert({ name, sprite }); }
	std::shared_ptr<Tmpl8::Sprite> get(const std::string& name) { return registry_[name]; }
private:
	std::map<std::string, std::shared_ptr<Tmpl8::Sprite>> registry_ = {};
};

extern SpriteRepository spriteRepository;
