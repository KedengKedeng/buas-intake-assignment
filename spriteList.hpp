#pragma once 
#include "spriteRepository.hpp"

// registers all used assets in the game to a list for lookup later
void setupSpriteList() {
	spriteRepository.insert("waterbottle", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/mcwaterbottle.png"), 1));
	spriteRepository.insert("playeridleleft", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playeridleleft.png"), 3));
	spriteRepository.insert("playeridleright", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playeridleright.png"), 3));
	spriteRepository.insert("playerwalkleft", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playerwalkleft.png"), 4));
	spriteRepository.insert("playerwalkright", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/playerwalkright.png"), 4));
	spriteRepository.insert("emptycauldron", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/emptycauldron.png"), 1));
	spriteRepository.insert("emptyburningcauldron", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/emptyburningcauldron.png"), 8));
	spriteRepository.insert("filledcauldron", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/filledcauldron.png"), 8));
	spriteRepository.insert("filledburningcauldron", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/filledburningcauldron.png"), 8));
	spriteRepository.insert("cauldroncloseupfront", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupfront.png"), 1));
	spriteRepository.insert("cauldroncloseupback", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupback.png"), 1));
	spriteRepository.insert("cauldroncloseupfire", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupfire.png"), 6));
	spriteRepository.insert("cauldroncloseupfilled", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/cauldroncloseupfilled.png"), 8));
	spriteRepository.insert("spoon", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/spoon.png"), 1));
	spriteRepository.insert("blower", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/blower.png"), 4));
	spriteRepository.insert("test", std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/testsprite.png"), 1));
}