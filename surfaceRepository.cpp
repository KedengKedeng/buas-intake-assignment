#include "surfaceRepository.hpp"

SurfaceRepository::SurfaceRepository() {
	// test surfaces
	insert(Surfaces::WaterBottle, std::make_shared<Tmpl8::Surface>("assets/items/mcwaterbottle.png"));

	//player
	insert(Surfaces::PlayerIdleLeft, std::make_shared<Tmpl8::Surface>("assets/characters/playeridleleft.png"));
	insert(Surfaces::PlayerIdleRight, std::make_shared<Tmpl8::Surface>("assets/characters/playeridleright.png"));
	insert(Surfaces::PlayerWalkLeft, std::make_shared<Tmpl8::Surface>("assets/characters/playerwalkleft.png"));
	insert(Surfaces::PlayerWalkRight, std::make_shared<Tmpl8::Surface>("assets/characters/playerwalkright.png"));

	//animals
	insert(Surfaces::BlueSlimeIdleLeft, std::make_shared<Tmpl8::Surface>("assets/animals/blueslimeidleleft.png"));
	insert(Surfaces::BlueSlimeIdleRight, std::make_shared<Tmpl8::Surface>("assets/animals/blueslimeidleright.png"));
	insert(Surfaces::BlueSlimeWalkLeft, std::make_shared<Tmpl8::Surface>("assets/animals/blueslimewalkleft.png"));
	insert(Surfaces::BlueSlimeWalkRight, std::make_shared<Tmpl8::Surface>("assets/animals/blueslimewalkright.png"));

	//cauldron
	insert(Surfaces::EmptyCauldron, std::make_shared<Tmpl8::Surface>("assets/cauldron/emptycauldron.png"));
	insert(Surfaces::EmptyBurningCauldron, std::make_shared<Tmpl8::Surface>("assets/cauldron/emptyburningcauldron.png"));
	insert(Surfaces::FilledCauldron, std::make_shared<Tmpl8::Surface>("assets/cauldron/filledcauldron.png"));
	insert(Surfaces::FilledBurningCauldron, std::make_shared<Tmpl8::Surface>("assets/cauldron/filledburningcauldron.png"));
	insert(Surfaces::CauldronCloseupFront, std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupfront.png"));
	insert(Surfaces::CauldronCloseupBack, std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupback.png"));
	insert(Surfaces::CauldronCloseupFire, std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupfire.png"));
	insert(Surfaces::CauldronCloseupFilled, std::make_shared<Tmpl8::Surface>("assets/cauldron/cauldroncloseupfilled.png"));

	insert(Surfaces::Spoon, std::make_shared<Tmpl8::Surface>("assets/spoon.png"));
	insert(Surfaces::Blower, std::make_shared<Tmpl8::Surface>("assets/blower.png"));

	insert(Surfaces::Floor, std::make_shared<Tmpl8::Surface>("assets/floor.png"));
}