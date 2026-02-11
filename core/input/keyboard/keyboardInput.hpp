#pragma once
#include "command.hpp"
#include <memory>
#include <map>
#include <functional>

enum class KeyFunctions {
	WalkLeft,
	WalkUp,
	WalkDown,
	WalkRight,
	Interact,
	Escape,
	Inventory,
	OpenShop,
	ResetCauldron
};

extern std::map<int, KeyFunctions> keyMapping;

class KeyboardInput {
public:
	void keyDown(int keyCode);
	void keyUp(int keyCode);

	void registerHandler(KeyFunctions action, std::function<std::unique_ptr<Command>()> handler) { handlers[action] = handler; }
	void clearKeysDown();
private:
	std::map<int, std::unique_ptr<Command>> keysDown = {};
	std::map<KeyFunctions, std::function<std::unique_ptr<Command>()>> handlers = {};
};