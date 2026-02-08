#include "spriteRepository.hpp"
#include "surfaceRepository.hpp"

SpriteRepository::SpriteRepository() {
	auto& repo = surfaceRepository();

	auto spoonSurface = repo.get(Surfaces::Spoon);
	insert(Sprites::Spoon, Sprite(spoonSurface, Rect2(20, 20, spoonSurface->GetWidth() - 40, spoonSurface->GetHeight() - 40)));

	//player
	insertSheet(SpriteSheets::PlayerIdleLeft, SpriteSheet(repo.get(Surfaces::PlayerIdleLeft), 1, 3));
	insertSheet(SpriteSheets::PlayerIdleRight, SpriteSheet(repo.get(Surfaces::PlayerIdleRight), 1, 3));
	insertSheet(SpriteSheets::PlayerWalkLeft, SpriteSheet(repo.get(Surfaces::PlayerWalkLeft), 1, 4));
	insertSheet(SpriteSheets::PlayerWalkRight, SpriteSheet(repo.get(Surfaces::PlayerWalkRight), 1, 4));

	//customers
	insertSheet(SpriteSheets::PenguinIdleLeft, SpriteSheet(repo.get(Surfaces::PenguinIdleLeft), 1, 3));
	insertSheet(SpriteSheets::PenguinIdleRight, SpriteSheet(repo.get(Surfaces::PenguinIdleRight), 1, 3));
	insertSheet(SpriteSheets::PenguinWalkLeft, SpriteSheet(repo.get(Surfaces::PenguinWalkLeft), 1, 4));
	insertSheet(SpriteSheets::PenguinWalkRight, SpriteSheet(repo.get(Surfaces::PenguinWalkRight), 1, 4));

	//animals
	insertSheet(SpriteSheets::BlueSlimeIdleLeft, SpriteSheet(repo.get(Surfaces::BlueSlimeIdleLeft), 1, 3));
	insertSheet(SpriteSheets::BlueSlimeIdleRight, SpriteSheet(repo.get(Surfaces::BlueSlimeIdleRight), 1, 3));
	insertSheet(SpriteSheets::BlueSlimeWalkLeft, SpriteSheet(repo.get(Surfaces::BlueSlimeWalkLeft), 1, 3));
	insertSheet(SpriteSheets::BlueSlimeWalkRight, SpriteSheet(repo.get(Surfaces::BlueSlimeWalkRight), 1, 3));
	insertSheet(SpriteSheets::GreenSlimeIdleLeft, SpriteSheet(repo.get(Surfaces::GreenSlimeIdleLeft), 1, 3));
	insertSheet(SpriteSheets::GreenSlimeIdleRight, SpriteSheet(repo.get(Surfaces::GreenSlimeIdleRight), 1, 3));
	insertSheet(SpriteSheets::GreenSlimeWalkLeft, SpriteSheet(repo.get(Surfaces::GreenSlimeWalkLeft), 1, 3));
	insertSheet(SpriteSheets::GreenSlimeWalkRight, SpriteSheet(repo.get(Surfaces::GreenSlimeWalkRight), 1, 3));
	insertSheet(SpriteSheets::IceDragonIdleLeft, SpriteSheet(repo.get(Surfaces::IceDragonIdleLeft), 1, 3));
	insertSheet(SpriteSheets::IceDragonIdleRight, SpriteSheet(repo.get(Surfaces::IceDragonIdleRight), 1, 3));
	insertSheet(SpriteSheets::IceDragonWalkLeft, SpriteSheet(repo.get(Surfaces::IceDragonWalkLeft), 1, 4));
	insertSheet(SpriteSheets::IceDragonWalkRight, SpriteSheet(repo.get(Surfaces::IceDragonWalkRight), 1, 4));
	insertSheet(SpriteSheets::WindDragonIdleLeft, SpriteSheet(repo.get(Surfaces::WindDragonIdleLeft), 1, 3));
	insertSheet(SpriteSheets::WindDragonIdleRight, SpriteSheet(repo.get(Surfaces::WindDragonIdleRight), 1, 3));
	insertSheet(SpriteSheets::WindDragonWalkLeft, SpriteSheet(repo.get(Surfaces::WindDragonWalkLeft), 1, 4));
	insertSheet(SpriteSheets::WindDragonWalkRight, SpriteSheet(repo.get(Surfaces::WindDragonWalkRight), 1, 4));
	insertSheet(SpriteSheets::EarthDragonIdleLeft, SpriteSheet(repo.get(Surfaces::EarthDragonIdleLeft), 1, 3));
	insertSheet(SpriteSheets::EarthDragonIdleRight, SpriteSheet(repo.get(Surfaces::EarthDragonIdleRight), 1, 3));
	insertSheet(SpriteSheets::EarthDragonWalkLeft, SpriteSheet(repo.get(Surfaces::EarthDragonWalkLeft), 1, 4));
	insertSheet(SpriteSheets::EarthDragonWalkRight, SpriteSheet(repo.get(Surfaces::EarthDragonWalkRight), 1, 4));
	insertSheet(SpriteSheets::FireDragonIdleLeft, SpriteSheet(repo.get(Surfaces::FireDragonIdleLeft), 1, 3));
	insertSheet(SpriteSheets::FireDragonIdleRight, SpriteSheet(repo.get(Surfaces::FireDragonIdleRight), 1, 3));
	insertSheet(SpriteSheets::FireDragonWalkLeft, SpriteSheet(repo.get(Surfaces::FireDragonWalkLeft), 1, 4));
	insertSheet(SpriteSheets::FireDragonWalkRight, SpriteSheet(repo.get(Surfaces::FireDragonWalkRight), 1, 4));

	//items
	insert(Sprites::BlueSlime, Sprite(repo.get(Surfaces::BlueSlime)));
	insert(Sprites::GreenSlime, Sprite(repo.get(Surfaces::GreenSlime)));
	insertSheet(SpriteSheets::IceGem, SpriteSheet(repo.get(Surfaces::IceGem), 1, 4));
	insertSheet(SpriteSheets::WindGem, SpriteSheet(repo.get(Surfaces::WindGem), 1, 4));
	insertSheet(SpriteSheets::EarthGem, SpriteSheet(repo.get(Surfaces::EarthGem), 1, 4));
	insertSheet(SpriteSheets::FireGem, SpriteSheet(repo.get(Surfaces::FireGem), 1, 4));

	insert(Sprites::SlipperyOrb, Sprite(repo.get(Surfaces::SlipperyOrb)));
	insert(Sprites::SlimeTape, Sprite(repo.get(Surfaces::SlimeTape)));
	insert(Sprites::RainBoots, Sprite(repo.get(Surfaces::RainBoots)));
	insert(Sprites::GliderWings, Sprite(repo.get(Surfaces::GliderWings)));
	insert(Sprites::StoneWheel, Sprite(repo.get(Surfaces::StoneWheel)));
	insert(Sprites::RocketBooster, Sprite(repo.get(Surfaces::RocketBooster)));
	insert(Sprites::StickyOrb, Sprite(repo.get(Surfaces::StickyOrb)));
	insert(Sprites::BurnCream, Sprite(repo.get(Surfaces::BurnCream)));
	insert(Sprites::GrapplingHook, Sprite(repo.get(Surfaces::GrapplingHook)));
	insert(Sprites::ClimbingGloves, Sprite(repo.get(Surfaces::ClimbingGloves)));
	insert(Sprites::StickyBomb, Sprite(repo.get(Surfaces::StickyBomb)));
	insert(Sprites::StormInABottle, Sprite(repo.get(Surfaces::StormInABottle)));
	insert(Sprites::WindCharge, Sprite(repo.get(Surfaces::WindCharge)));
	insert(Sprites::ShipInABottle, Sprite(repo.get(Surfaces::ShipInABottle)));
	insert(Sprites::LightningGem, Sprite(repo.get(Surfaces::LightningGem)));
	insert(Sprites::SlipperyOrb, Sprite(repo.get(Surfaces::SlipperyOrb)));
	insert(Sprites::IceScates, Sprite(repo.get(Surfaces::IceScates)));
	insert(Sprites::MuddyBlob, Sprite(repo.get(Surfaces::MuddyBlob)));
	insert(Sprites::ObsidianGem, Sprite(repo.get(Surfaces::ObsidianGem)));
	insert(Sprites::ClayBall, Sprite(repo.get(Surfaces::ClayBall)));
	insert(Sprites::MagmaBall, Sprite(repo.get(Surfaces::MagmaBall)));
	insert(Sprites::FireCharge, Sprite(repo.get(Surfaces::FireCharge)));

	//cauldron
	insertSheet(SpriteSheets::EmptyBurningCauldron, SpriteSheet(repo.get(Surfaces::EmptyBurningCauldron), 1, 8));
	insertSheet(SpriteSheets::FilledCauldron, SpriteSheet(repo.get(Surfaces::FilledCauldron), 1, 8));
	insertSheet(SpriteSheets::FilledBurningCauldron, SpriteSheet(repo.get(Surfaces::FilledBurningCauldron), 1, 8));
	insertSheet(SpriteSheets::CauldronCloseupFire, SpriteSheet(repo.get(Surfaces::CauldronCloseupFire), 1, 6));
	insertSheet(SpriteSheets::CauldronCloseupFilled, SpriteSheet(repo.get(Surfaces::CauldronCloseupFilled), 1, 8));
	insert(Sprites::EmptyCauldron, Sprite(repo.get(Surfaces::EmptyCauldron)));
	insert(Sprites::CauldronCloseupFront, Sprite(repo.get(Surfaces::CauldronCloseupFront)));
	insert(Sprites::CauldronCloseupBack, Sprite(repo.get(Surfaces::CauldronCloseupBack)));

	insertSheet(SpriteSheets::Blower, SpriteSheet(repo.get(Surfaces::Blower), 1, 4));
	insertSheet(SpriteSheets::Floor, SpriteSheet(repo.get(Surfaces::Floor), 2, 2));
}