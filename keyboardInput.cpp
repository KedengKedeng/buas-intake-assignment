#include "keyboardInput.hpp"
#include "moveCommand.hpp"
#include "interactionCommand.hpp"
#include "keyboardCommand.hpp"
#include "template.h"
#include <vector>

std::map<int, std::string> keyMapping = {
	{4, "walkLeft"},
	{26, "walkUp"},
	{22, "walkDown"},
	{7, "walkRight"},
	{40, "interact"},
	{41, "escape"}
};

void KeyboardInput::keyDown(int keyCode) {
	// If we dont do this commands will continuously get triggered
	// by holding down a key.
	if (keysDown.count(keyCode)) return;
	else if (keyMapping.count(keyCode) && handlers.count(keyMapping[keyCode])) {
		keysDown[keyCode] = handlers[keyMapping[keyCode]](); 
		keysDown[keyCode]->execute();
	}
	else printf("keycode: %d\n", keyCode);
}

void KeyboardInput::keyUp(int keyCode) {
	if (keysDown.count(keyCode)) keysDown[keyCode]->undo();
	keysDown.erase(keyCode);
}

void KeyboardInput::clearKeysDown() {
	for (auto currentKeyDown = keysDown.begin(); currentKeyDown != keysDown.end(); currentKeyDown++)
		currentKeyDown->second->undo();

	keysDown.clear();
}