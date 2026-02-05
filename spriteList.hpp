#pragma once 
#include "spriteRepository.hpp"
#include "surfaceRepository.hpp"

// registers all used assets in the game to a list for lookup later
void setupSpriteList() {
	auto& repo = surfaceRepository();
	spriteRepository.insert("waterbottle", Sprite(repo.get(Surfaces::WaterBottle)));
	spriteRepository.insert("spoon", Sprite(repo.get(Surfaces::Spoon)));

	//player
	spriteRepository.insertSheet("playeridleleft", SpriteSheet(repo.get(Surfaces::PlayerIdleLeft), 1, 3));
	spriteRepository.insertSheet("playeridleright", SpriteSheet(repo.get(Surfaces::PlayerIdleRight), 1, 3));
	spriteRepository.insertSheet("playerwalkleft", SpriteSheet(repo.get(Surfaces::PlayerWalkLeft), 1, 4));
	spriteRepository.insertSheet("playerwalkright", SpriteSheet(repo.get(Surfaces::PlayerWalkRight), 1, 4));

	//animals
	spriteRepository.insertSheet("blueslimeidleleft", SpriteSheet(repo.get(Surfaces::BlueSlimeIdleLeft), 1, 3));
	spriteRepository.insertSheet("blueslimeidleright", SpriteSheet(repo.get(Surfaces::BlueSlimeIdleRight), 1, 3));
	spriteRepository.insertSheet("blueslimewalkleft", SpriteSheet(repo.get(Surfaces::BlueSlimeWalkLeft), 1, 3));
	spriteRepository.insertSheet("blueslimewalkright", SpriteSheet(repo.get(Surfaces::BlueSlimeWalkRight), 1, 3));

	//cauldron
	spriteRepository.insertSheet("emptyburningcauldron", SpriteSheet(repo.get(Surfaces::EmptyBurningCauldron), 1, 8));
	spriteRepository.insertSheet("filledcauldron", SpriteSheet(repo.get(Surfaces::FilledCauldron), 1, 8));
	spriteRepository.insertSheet("filledburningcauldron", SpriteSheet(repo.get(Surfaces::FilledBurningCauldron), 1, 8));
	spriteRepository.insertSheet("cauldroncloseupfire", SpriteSheet(repo.get(Surfaces::CauldronCloseupFire), 1, 6));
	spriteRepository.insertSheet("cauldroncloseupfilled", SpriteSheet(repo.get(Surfaces::CauldronCloseupFilled), 1, 8));
	spriteRepository.insert("emptycauldron", Sprite(repo.get(Surfaces::EmptyCauldron)));
	spriteRepository.insert("cauldroncloseupfront", Sprite(repo.get(Surfaces::CauldronCloseupFront)));
	spriteRepository.insert("cauldroncloseupback", Sprite(repo.get(Surfaces::CauldronCloseupBack)));

	spriteRepository.insertSheet("blower", SpriteSheet(repo.get(Surfaces::Blower), 1, 4));
	spriteRepository.insertSheet("floor", SpriteSheet(repo.get(Surfaces::Floor), 2, 2));
}