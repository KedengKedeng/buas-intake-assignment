#pragma once 
#include "spriteRepository.hpp"
#include "surfaceRepository.hpp"

// registers all used assets in the game to a list for lookup later
void setupSpriteList() {
	spriteRepository.insert("waterbottle", Sprite(surfaceRepository.get("waterbottle"), 1));
	spriteRepository.insert("playeridleleft", Sprite(surfaceRepository.get("playeridleleft"), 3));
	spriteRepository.insert("playeridleright", Sprite(surfaceRepository.get("playeridleright"), 3));
	spriteRepository.insert("playerwalkleft", Sprite(surfaceRepository.get("playerwalkleft"), 4));
	spriteRepository.insert("playerwalkright", Sprite(surfaceRepository.get("playerwalkright"), 4));
	spriteRepository.insert("emptycauldron", Sprite(surfaceRepository.get("emptycauldron"), 1));
	spriteRepository.insert("emptyburningcauldron", Sprite(surfaceRepository.get("emptyburningcauldron"), 8));
	spriteRepository.insert("filledcauldron", Sprite(surfaceRepository.get("filledcauldron"), 8));
	spriteRepository.insert("filledburningcauldron", Sprite(surfaceRepository.get("filledburningcauldron"), 8));
	spriteRepository.insert("cauldroncloseupfront", Sprite(surfaceRepository.get("cauldroncloseupfront"), 1));
	spriteRepository.insert("cauldroncloseupback", Sprite(surfaceRepository.get("cauldroncloseupback"), 1));
	spriteRepository.insert("cauldroncloseupfire", Sprite(surfaceRepository.get("cauldroncloseupfire"), 6));
	spriteRepository.insert("cauldroncloseupfilled", Sprite(surfaceRepository.get("cauldroncloseupfilled"), 8));
	spriteRepository.insert("spoon", Sprite(surfaceRepository.get("spoon"), 1));
	spriteRepository.insert("blower", Sprite(surfaceRepository.get("blower"), 4));
	spriteRepository.insert("test", Sprite(surfaceRepository.get("test"), 1));
}