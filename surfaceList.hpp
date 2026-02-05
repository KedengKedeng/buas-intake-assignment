#pragma once 
#include "surfaceRepository.hpp"

// registers all used assets in the game to a list for lookup later
void setupSurfaceList() {
	// test surfaces
	surfaceRepository.insert("waterbottle", std::make_shared<Tmpl8::Surface>("assets/items/mcwaterbottle.png"));
	surfaceRepository.insert("test", std::make_shared<Tmpl8::Surface>("assets/testsprite.png"));

	//player
	surfaceRepository.insert("playeridleleft", std::make_shared<Tmpl8::Surface>("assets/characters/playeridleleft.png"));
	surfaceRepository.insert("playeridleright", std::make_shared<Tmpl8::Surface>("assets/characters/playeridleright.png"));
	surfaceRepository.insert("playerwalkleft", std::make_shared<Tmpl8::Surface>("assets/characters/playerwalkleft.png"));
	surfaceRepository.insert("playerwalkright", std::make_shared<Tmpl8::Surface>("assets/characters/playerwalkright.png"));

	//animals
	surfaceRepository.insert("blueslimeidleleft", std::make_shared<Tmpl8::Surface>("assets/animals/blueslimeidleleft.png"));
	surfaceRepository.insert("blueslimeidleright", std::make_shared<Tmpl8::Surface>("assets/animals/blueslimeidleright.png"));
	surfaceRepository.insert("blueslimewalkleft", std::make_shared<Tmpl8::Surface>("assets/animals/blueslimewalkleft.png"));
	surfaceRepository.insert("blueslimewalkright", std::make_shared<Tmpl8::Surface>("assets/animals/blueslimewalkright.png"));

	//cauldron
	surfaceRepository.insert("emptycauldron", std::make_shared<Tmpl8::Surface>("assets/cauldron/emptycauldron.png"));
	surfaceRepository.insert("emptyburningcauldron", std::make_shared<Tmpl8::Surface>("assets/cauldron/emptyburningcauldron.png"));
	surfaceRepository.insert("filledcauldron", std::make_shared<Tmpl8::Surface>("assets/cauldron/filledcauldron.png"));
	surfaceRepository.insert("filledburningcauldron", std::make_shared<Tmpl8::Surface>("assets/cauldron/filledburningcauldron.png"));
	surfaceRepository.insert("cauldroncloseupfront", std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupfront.png"));
	surfaceRepository.insert("cauldroncloseupback", std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupback.png"));
	surfaceRepository.insert("cauldroncloseupfire", std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupfire.png"));
	surfaceRepository.insert("cauldroncloseupfilled", std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupfilled.png"));

	surfaceRepository.insert("spoon", std::make_shared<Tmpl8::Surface>("assets/spoon.png"));
	surfaceRepository.insert("blower", std::make_shared<Tmpl8::Surface>("assets/blower.png"));

	surfaceRepository.insert("floor", std::make_shared<Tmpl8::Surface>("assets/floor.png"));
}