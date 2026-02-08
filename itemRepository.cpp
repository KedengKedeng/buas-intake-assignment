#include "itemsRepository.hpp"
#include "spriteRepository.hpp"

ItemRepository::ItemRepository() {
	insert(std::make_shared<Item>(
		Items::BlueSlime,
		"Blue Slime",
		0,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::BlueSlime, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::GreenSlime,
		"Green Slime",
		0,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::GreenSlime, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::IceGem,
		"Ice Gem",
		0,
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::IceGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::WindGem,
		"Wind Gem",
		0,
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::WindGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::EarthGem,
		"Earth Gem",
		0,
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::EarthGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::FireGem,
		"Fire Gem",
		0,
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::FireGem), 0.002f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::SlipperyOrb,
		"Slippery Orb",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::SlipperyOrb, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::SlimeTape,
		"Slime Tape",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::SlimeTape, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::RainBoots,
		"Rain Boots",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::RainBoots, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::GliderWings,
		"Glider Wings",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::GliderWings, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StoneWheel,
		"Stone Wheel",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StoneWheel, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::RocketBooster,
		"Rocket Booster",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::RocketBooster, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StickyOrb,
		"Sticky Orb",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StickyOrb, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::BurnCream,
		"Burn Cream",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::BurnCream, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::GrapplingHook,
		"Grappling Hook",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::GrapplingHook, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ClimbingGloves,
		"Climbing Gloves",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ClimbingGloves, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StickyBomb,
		"Sticky Bomb",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StickyBomb, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::StormInABottle,
		"Storm In A Bottle",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::StormInABottle, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::WindCharge,
		"Wind Charge",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::WindCharge, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ShipInABottle,
		"Ship In A Bottle",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ShipInABottle, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::LightningGem,
		"Lightning Gem",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::LightningGem, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::IceScates,
		"Ice Scates",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::IceScates, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::MuddyBlob,
		"Muddy Blob",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::MuddyBlob, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ObsidianGem,
		"Obsidian Gem",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ObsidianGem, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::ClayBall,
		"Clay Ball",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::ClayBall, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::MagmaBall,
		"Magma Ball",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::MagmaBall, 1.0f)), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::FireCharge,
		"Fire Charge",
		10,
		AnimatedSprite(std::make_shared<SpriteSheet>(spriteRepository().get(Sprites::FireCharge, 1.0f)), 0.0f, 1.0f)
	));
}