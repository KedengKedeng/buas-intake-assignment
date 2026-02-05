#include "spriteRepository.hpp"
#include "surfaceRepository.hpp"

SpriteRepository::SpriteRepository() {
	auto& repo = surfaceRepository();

	insert(Sprites::WaterBottle, Sprite(repo.get(Surfaces::WaterBottle)));
	insert(Sprites::Spoon, Sprite(repo.get(Surfaces::Spoon)));

	//player
	insertSheet(SpriteSheets::PlayerIdleLeft, SpriteSheet(repo.get(Surfaces::PlayerIdleLeft), 1, 3));
	insertSheet(SpriteSheets::PlayerIdleRight, SpriteSheet(repo.get(Surfaces::PlayerIdleRight), 1, 3));
	insertSheet(SpriteSheets::PlayerWalkLeft, SpriteSheet(repo.get(Surfaces::PlayerWalkLeft), 1, 4));
	insertSheet(SpriteSheets::PlayerWalkRight, SpriteSheet(repo.get(Surfaces::PlayerWalkRight), 1, 4));

	//animals
	insertSheet(SpriteSheets::BlueSlimeIdleLeft, SpriteSheet(repo.get(Surfaces::BlueSlimeIdleLeft), 1, 3));
	insertSheet(SpriteSheets::BlueSlimeIdleRight, SpriteSheet(repo.get(Surfaces::BlueSlimeIdleRight), 1, 3));
	insertSheet(SpriteSheets::BlueSlimeWalkLeft, SpriteSheet(repo.get(Surfaces::BlueSlimeWalkLeft), 1, 3));
	insertSheet(SpriteSheets::BlueSlimeWalkRight, SpriteSheet(repo.get(Surfaces::BlueSlimeWalkRight), 1, 3));

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