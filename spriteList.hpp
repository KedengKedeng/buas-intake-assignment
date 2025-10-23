#pragma once 
#include "spriteRepository.hpp"

void setupSpriteList() {
	spriteRepository.insert(std::string("rotatingGun"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/aagun.tga"), 36));
	spriteRepository.insert(std::string("cauldron"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/turret.tga"), 24));
	spriteRepository.insert(std::string("waterbottle"), std::make_shared< Tmpl8::Sprite>(new Tmpl8::Surface("assets/mcwaterbottle.png"), 1));
}