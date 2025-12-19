#pragma once 
#include "spriteRepository.hpp"
#include "surfaceRepository.hpp"

// registers all used assets in the game to a list for lookup later
void setupSpriteList() {
	spriteRepository.insert("waterbottle", Sprite(surfaceRepository.get("waterbottle")));
	spriteRepository.insert("emptycauldron", Sprite(surfaceRepository.get("emptycauldron")));
	spriteRepository.insert("cauldroncloseupfront", Sprite(surfaceRepository.get("cauldroncloseupfront")));
	spriteRepository.insert("cauldroncloseupback", Sprite(surfaceRepository.get("cauldroncloseupback")));
	spriteRepository.insert("spoon", Sprite(surfaceRepository.get("spoon")));
	spriteRepository.insert("test", Sprite(surfaceRepository.get("test")));

	spriteRepository.insertAnimated("playeridleleft", AnimatedSprite(surfaceRepository.get("playeridleleft"), 3, 0, 1));
	spriteRepository.insertAnimated("playeridleright", AnimatedSprite(surfaceRepository.get("playeridleright"), 3, 0, 1));
	spriteRepository.insertAnimated("playerwalkleft", AnimatedSprite(surfaceRepository.get("playerwalkleft"), 4, 0, 1));
	spriteRepository.insertAnimated("playerwalkright", AnimatedSprite(surfaceRepository.get("playerwalkright"), 4, 0, 1));
	spriteRepository.insertAnimated("emptyburningcauldron", AnimatedSprite(surfaceRepository.get("emptyburningcauldron"), 8, 0, 1));
	spriteRepository.insertAnimated("filledcauldron", AnimatedSprite(surfaceRepository.get("filledcauldron"), 8, 0, 1));
	spriteRepository.insertAnimated("filledburningcauldron", AnimatedSprite(surfaceRepository.get("filledburningcauldron"), 8, 0, 1));
	spriteRepository.insertAnimated("cauldroncloseupfire", AnimatedSprite(surfaceRepository.get("cauldroncloseupfire"), 6, 0, 1));
	spriteRepository.insertAnimated("cauldroncloseupfilled", AnimatedSprite(surfaceRepository.get("cauldroncloseupfilled"), 8, 0, 1));
	spriteRepository.insertAnimated("blower", AnimatedSprite(surfaceRepository.get("blower"), 4, 0, 1));
}