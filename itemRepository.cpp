#include "itemsRepository.hpp"
#include "spriteRepository.hpp"

ItemRepository::ItemRepository() {
	insert(std::make_shared<Item>(
		Items::BlueSlime,
		"Blue Slime",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::BlueSlime, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::GreenSlime,
		"Green Slime",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::GreenSlime, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::IceGem,
		"Ice Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::IceGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::WindGem,
		"Wind Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::WindGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::EarthGem,
		"Earth Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::EarthGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::FireGem,
		"Fire Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::FireGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::SlipperyOrb,
		"Slippery Orb",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::SlipperyOrb, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::SlimeTape,
		"Slime Tape",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::SlimeTape, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::RainBoots,
		"Rain Boots",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::RainBoots, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::GliderWings,
		"Glider Wings",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::GliderWings, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StoneWheel,
		"Stone Wheel",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StoneWheel, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::RocketBooster,
		"Rocket Booster",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::RocketBooster, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StickyOrb,
		"Sticky Orb",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StickyOrb, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::BurnCream,
		"Burn Cream",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::BurnCream, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::GrapplingHook,
		"Grappling Hook",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::GrapplingHook, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ClimbingGloves,
		"Climbing Gloves",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ClimbingGloves, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StickyBomb,
		"Sticky Bomb",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StickyBomb, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StormInABottle,
		"Storm In A Bottle",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StormInABottle, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::WindCharge,
		"Wind Charge",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::WindCharge, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ShipInABottle,
		"Ship In A Bottle",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ShipInABottle, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::LightningGem,
		"Lightning Gem",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::LightningGem, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::IceScates,
		"Ice Scates",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::IceScates, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::MuddyBlob,
		"Muddy Blob",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::MuddyBlob, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ObsidianGem,
		"Obsidian Gem",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ObsidianGem, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ClayBall,
		"Clay Ball",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ClayBall, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::MagmaBall,
		"Magma Ball",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::MagmaBall, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::FireCharge,
		"Fire Charge",
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::FireCharge, 1.0f)), 0.0f, 1.0f)
	));
}