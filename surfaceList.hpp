#pragma once 
#include "surfaceRepository.hpp"

// registers all used assets in the game to a list for lookup later
void setupSurfaceList() {
	surfaceRepository.insert("waterbottle", std::make_shared<Tmpl8::Surface>("assets/mcwaterbottle.png"));
	surfaceRepository.insert("playeridleleft", std::make_shared<Tmpl8::Surface>("assets/playeridleleft.png"));
	surfaceRepository.insert("playeridleright", std::make_shared<Tmpl8::Surface>("assets/playeridleright.png"));
	surfaceRepository.insert("playerwalkleft", std::make_shared<Tmpl8::Surface>("assets/playerwalkleft.png"));
	surfaceRepository.insert("playerwalkright", std::make_shared<Tmpl8::Surface>("assets/playerwalkright.png"));
	surfaceRepository.insert("emptycauldron", std::make_shared<Tmpl8::Surface>("assets/emptycauldron.png"));
	surfaceRepository.insert("emptyburningcauldron", std::make_shared<Tmpl8::Surface>("assets/emptyburningcauldron.png"));
	surfaceRepository.insert("filledcauldron", std::make_shared<Tmpl8::Surface>("assets/filledcauldron.png"));
	surfaceRepository.insert("filledburningcauldron", std::make_shared<Tmpl8::Surface>("assets/filledburningcauldron.png"));
	surfaceRepository.insert("cauldroncloseupfront", std::make_shared<Tmpl8::Surface>("assets/cauldroncloseupfront.png"));
	surfaceRepository.insert("cauldroncloseupback", std::make_shared<Tmpl8::Surface>("assets/cauldroncloseupback.png"));
	surfaceRepository.insert("cauldroncloseupfire", std::make_shared<Tmpl8::Surface>("assets/cauldroncloseupfire.png"));
	surfaceRepository.insert("cauldroncloseupfilled", std::make_shared<Tmpl8::Surface>("assets/cauldroncloseupfilled.png"));
	surfaceRepository.insert("spoon", std::make_shared<Tmpl8::Surface>("assets/spoon.png"));
	surfaceRepository.insert("blower", std::make_shared<Tmpl8::Surface>("assets/blower.png"));
	surfaceRepository.insert("test", std::make_shared<Tmpl8::Surface>("assets/testsprite.png"));
}