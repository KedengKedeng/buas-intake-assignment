#include "customerTypeRepository.hpp"
#include "spriteRepository.hpp"

CustomerTypeRepository::CustomerTypeRepository() {
	constexpr float scale = 2.5f;
	constexpr float frameRate = 0.005f;
	auto spriteRepo = spriteRepository();

	insert(std::make_shared<CustomerType>(
		CustomerTypes::Penguin,
		"Penguin",
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::PenguinIdleLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::PenguinIdleRight), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::PenguinWalkLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::PenguinWalkRight), frameRate, scale)
	));
}