#include "surfaceRepository.hpp"

SurfaceRepository::SurfaceRepository() {
	//player
	insert(Surfaces::PlayerIdleLeft, std::make_shared<Tmpl8::Surface>("assets/characters/playeridleleft.png"));
	insert(Surfaces::PlayerIdleRight, std::make_shared<Tmpl8::Surface>("assets/characters/playeridleright.png"));
	insert(Surfaces::PlayerWalkLeft, std::make_shared<Tmpl8::Surface>("assets/characters/playerwalkleft.png"));
	insert(Surfaces::PlayerWalkRight, std::make_shared<Tmpl8::Surface>("assets/characters/playerwalkright.png"));

	//customers
	insert(Surfaces::PenguinIdleLeft, std::make_shared<Tmpl8::Surface>("assets/characters/penguinidleleft.png"));
	insert(Surfaces::PenguinIdleRight, std::make_shared<Tmpl8::Surface>("assets/characters/penguinidleright.png"));
	insert(Surfaces::PenguinWalkLeft, std::make_shared<Tmpl8::Surface>("assets/characters/penguinwalkleft.png"));
	insert(Surfaces::PenguinWalkRight, std::make_shared<Tmpl8::Surface>("assets/characters/penguinwalkright.png"));

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

	//items
	insert(Surfaces::BlueSlime, std::make_shared<Tmpl8::Surface>("assets/items/blueslime.png"));
	insert(Surfaces::GreenSlime, std::make_shared<Tmpl8::Surface>("assets/items/greenslime.png"));
	insert(Surfaces::IceGem, std::make_shared<Tmpl8::Surface>("assets/items/icegem.png"));
	insert(Surfaces::WindGem, std::make_shared<Tmpl8::Surface>("assets/items/windgem.png"));
	insert(Surfaces::EarthGem, std::make_shared<Tmpl8::Surface>("assets/items/earthgem.png"));
	insert(Surfaces::FireGem, std::make_shared<Tmpl8::Surface>("assets/items/firegem.png"));

	insert(Surfaces::SlipperyOrb, std::make_shared<Tmpl8::Surface>("assets/items/slipperyorb.png"));
	insert(Surfaces::SlimeTape, std::make_shared<Tmpl8::Surface>("assets/items/slimetape.png"));
	insert(Surfaces::RainBoots, std::make_shared<Tmpl8::Surface>("assets/items/rainboots.png"));
	insert(Surfaces::GliderWings, std::make_shared<Tmpl8::Surface>("assets/items/gliderwings.png"));
	insert(Surfaces::StoneWheel, std::make_shared<Tmpl8::Surface>("assets/items/stonewheel.png"));
	insert(Surfaces::RocketBooster, std::make_shared<Tmpl8::Surface>("assets/items/rocketbooster.png"));
	insert(Surfaces::StickyOrb, std::make_shared<Tmpl8::Surface>("assets/items/stickyorb.png"));
	insert(Surfaces::BurnCream, std::make_shared<Tmpl8::Surface>("assets/items/burncream.png"));
	insert(Surfaces::GrapplingHook, std::make_shared<Tmpl8::Surface>("assets/items/grapplinghook.png"));
	insert(Surfaces::ClimbingGloves, std::make_shared<Tmpl8::Surface>("assets/items/climbinggloves.png"));
	insert(Surfaces::StickyBomb, std::make_shared<Tmpl8::Surface>("assets/items/stickybomb.png"));
	insert(Surfaces::StormInABottle, std::make_shared<Tmpl8::Surface>("assets/items/storminabottle.png"));
	insert(Surfaces::WindCharge, std::make_shared<Tmpl8::Surface>("assets/items/windcharge.png"));
	insert(Surfaces::ShipInABottle, std::make_shared<Tmpl8::Surface>("assets/items/shipinabottle.png"));
	insert(Surfaces::LightningGem, std::make_shared<Tmpl8::Surface>("assets/items/lightninggem.png"));
	insert(Surfaces::IceScates, std::make_shared<Tmpl8::Surface>("assets/items/icescates.png"));
	insert(Surfaces::MuddyBlob, std::make_shared<Tmpl8::Surface>("assets/items/muddyblob.png"));
	insert(Surfaces::ObsidianGem, std::make_shared<Tmpl8::Surface>("assets/items/obsidiangem.png"));
	insert(Surfaces::ClayBall, std::make_shared<Tmpl8::Surface>("assets/items/clayball.png"));
	insert(Surfaces::MagmaBall, std::make_shared<Tmpl8::Surface>("assets/items/magmaball.png"));
	insert(Surfaces::FireCharge, std::make_shared<Tmpl8::Surface>("assets/items/firecharge.png"));


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

	insert(Surfaces::Sign, std::make_shared<Tmpl8::Surface>("assets/sign.png"));

	insert(Surfaces::Floor, std::make_shared<Tmpl8::Surface>("assets/floor.png"));
}