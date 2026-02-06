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
	insert(Surfaces::GreenSlimeIdleLeft, std::make_shared<Tmpl8::Surface>("assets/animals/greenslimeidleleft.png"));
	insert(Surfaces::GreenSlimeIdleRight, std::make_shared<Tmpl8::Surface>("assets/animals/greenslimeidleright.png"));
	insert(Surfaces::GreenSlimeWalkLeft, std::make_shared<Tmpl8::Surface>("assets/animals/greenslimewalkleft.png"));
	insert(Surfaces::GreenSlimeWalkRight, std::make_shared<Tmpl8::Surface>("assets/animals/greenslimewalkright.png"));
	insert(Surfaces::IceDragonIdleLeft, std::make_shared<Tmpl8::Surface>("assets/animals/icedragonidleleft.png"));
	insert(Surfaces::IceDragonIdleRight, std::make_shared<Tmpl8::Surface>("assets/animals/icedragonidleright.png"));
	insert(Surfaces::IceDragonWalkLeft, std::make_shared<Tmpl8::Surface>("assets/animals/icedragonwalkleft.png"));
	insert(Surfaces::IceDragonWalkRight, std::make_shared<Tmpl8::Surface>("assets/animals/icedragonwalkright.png"));
	insert(Surfaces::WindDragonIdleLeft, std::make_shared<Tmpl8::Surface>("assets/animals/winddragonidleleft.png"));
	insert(Surfaces::WindDragonIdleRight, std::make_shared<Tmpl8::Surface>("assets/animals/winddragonidleright.png"));
	insert(Surfaces::WindDragonWalkLeft, std::make_shared<Tmpl8::Surface>("assets/animals/winddragonwalkleft.png"));
	insert(Surfaces::WindDragonWalkRight, std::make_shared<Tmpl8::Surface>("assets/animals/winddragonwalkright.png"));
	insert(Surfaces::EarthDragonIdleLeft, std::make_shared<Tmpl8::Surface>("assets/animals/earthdragonidleleft.png"));
	insert(Surfaces::EarthDragonIdleRight, std::make_shared<Tmpl8::Surface>("assets/animals/earthdragonidleright.png"));
	insert(Surfaces::EarthDragonWalkLeft, std::make_shared<Tmpl8::Surface>("assets/animals/earthdragonwalkleft.png"));
	insert(Surfaces::EarthDragonWalkRight, std::make_shared<Tmpl8::Surface>("assets/animals/earthdragonwalkright.png"));
	insert(Surfaces::FireDragonIdleLeft, std::make_shared<Tmpl8::Surface>("assets/animals/firedragonidleleft.png"));
	insert(Surfaces::FireDragonIdleRight, std::make_shared<Tmpl8::Surface>("assets/animals/firedragonidleright.png"));
	insert(Surfaces::FireDragonWalkLeft, std::make_shared<Tmpl8::Surface>("assets/animals/firedragonwalkleft.png"));
	insert(Surfaces::FireDragonWalkRight, std::make_shared<Tmpl8::Surface>("assets/animals/firedragonwalkright.png"));

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