#include "itemsRepository.hpp"
#include "spriteRepository.hpp"

ItemRepository::ItemRepository() {
	insert(std::make_shared<Item>(
		Items::BlueSlime,
		"Blue Slime",
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{ spriteRepository().get(Sprites::BlueSlime, 1.0f) }), 0.0f, 1.0f)
	));

	insert(std::make_shared<Item>(
		Items::GreenSlime,
		"Green Slime",
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{ spriteRepository().get(Sprites::GreenSlime, 1.0f) }), 0.0f, 1.0f)
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

	const float playerSpriteScale = 2;
	const float playerSpriteFrameRate = 0.005f;
	auto playerIdleLeft = AnimatedSprite(spriteRepository().getSheet(SpriteSheets::PlayerIdleLeft), playerSpriteFrameRate, playerSpriteScale);

	insert(std::make_shared<Item>(
		Items::Test,
		"testItem3",
		playerIdleLeft
	));
}