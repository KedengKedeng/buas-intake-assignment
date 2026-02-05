#pragma once 
#include "spriteRepository.hpp"
#include "surfaceRepository.hpp"

// registers all used assets in the game to a list for lookup later
void setupSpriteList() {
	spriteRepository.insert("waterbottle", Sprite(surfaceRepository.get("waterbottle")));
	spriteRepository.insert("spoon", Sprite(surfaceRepository.get("spoon")));
	spriteRepository.insert("test", Sprite(surfaceRepository.get("test")));

	//player
	spriteRepository.insertSheet("playeridleleft", SpriteSheet(surfaceRepository.get("playeridleleft"), 1, 3));
	spriteRepository.insertSheet("playeridleright", SpriteSheet(surfaceRepository.get("playeridleright"), 1, 3));
	spriteRepository.insertSheet("playerwalkleft", SpriteSheet(surfaceRepository.get("playerwalkleft"), 1, 4));
	spriteRepository.insertSheet("playerwalkright", SpriteSheet(surfaceRepository.get("playerwalkright"), 1, 4));

	//animals
	spriteRepository.insertSheet("blueslimeidleleft", SpriteSheet(surfaceRepository.get("blueslimeidleleft"), 1, 3));
	spriteRepository.insertSheet("blueslimeidleright", SpriteSheet(surfaceRepository.get("blueslimeidleright"), 1, 3));
	spriteRepository.insertSheet("blueslimewalkleft", SpriteSheet(surfaceRepository.get("blueslimewalkleft"), 1, 3));
	spriteRepository.insertSheet("blueslimewalkright", SpriteSheet(surfaceRepository.get("blueslimewalkright"), 1, 3));

	//cauldron
	spriteRepository.insertSheet("emptyburningcauldron", SpriteSheet(surfaceRepository.get("emptyburningcauldron"), 1, 8));
	spriteRepository.insertSheet("filledcauldron", SpriteSheet(surfaceRepository.get("filledcauldron"), 1, 8));
	spriteRepository.insertSheet("filledburningcauldron", SpriteSheet(surfaceRepository.get("filledburningcauldron"), 1, 8));
	spriteRepository.insertSheet("cauldroncloseupfire", SpriteSheet(surfaceRepository.get("cauldroncloseupfire"), 1, 6));
	spriteRepository.insertSheet("cauldroncloseupfilled", SpriteSheet(surfaceRepository.get("cauldroncloseupfilled"), 1, 8));
	spriteRepository.insert("emptycauldron", Sprite(surfaceRepository.get("emptycauldron")));
	spriteRepository.insert("cauldroncloseupfront", Sprite(surfaceRepository.get("cauldroncloseupfront")));
	spriteRepository.insert("cauldroncloseupback", Sprite(surfaceRepository.get("cauldroncloseupback")));

	spriteRepository.insertSheet("blower", SpriteSheet(surfaceRepository.get("blower"), 1, 4));
	spriteRepository.insertSheet("floor", SpriteSheet(surfaceRepository.get("floor"), 2, 2));
}