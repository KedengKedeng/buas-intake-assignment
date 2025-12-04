#pragma once 
#include "spriteRepository.hpp"

void setupSpriteList() {
	spriteRepository.insert(std::string("waterbottle"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/mcwaterbottle.png"), 1));
	spriteRepository.insert(std::string("playeridleleft"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playeridleleft.png"), 3));
	spriteRepository.insert(std::string("playeridleright"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playeridleright.png"), 3));
	spriteRepository.insert(std::string("playerwalkleft"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playerwalkleft.png"), 4));
	spriteRepository.insert(std::string("playerwalkright"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playerwalkright.png"), 4));
	spriteRepository.insert(std::string("emptycauldron"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/emptycauldron.png"), 1));
	spriteRepository.insert(std::string("emptyburningcauldron"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/emptyburningcauldron.png"), 8));
	spriteRepository.insert(std::string("filledcauldron"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/filledcauldron.png"), 8));
	spriteRepository.insert(std::string("filledburningcauldron"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/filledburningcauldron.png"), 8));
	spriteRepository.insert(std::string("cauldroncloseupfront"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupfront.png"), 1));
	spriteRepository.insert(std::string("cauldroncloseupback"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupback.png"), 1));
	spriteRepository.insert(std::string("cauldroncloseupfire"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupfire.png"), 6));
	spriteRepository.insert(std::string("cauldroncloseupfilled"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupfilled.png"), 8));
	spriteRepository.insert(std::string("spoon"), std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/spoon.png"), 1));

}