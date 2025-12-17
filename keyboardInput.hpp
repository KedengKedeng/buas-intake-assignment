#pragma once
#include "command.hpp"
#include <string>
#include <memory>
#include <map>
#include <functional>

extern std::map<int, std::string> keyMapping;

class KeyboardInput {
public:
	void keyDown(int keyCode);
	void keyUp(int keyCode);

	void registerHandler(const std::string& action, std::function<std::unique_ptr<Command>()> handler) { handlers[action] = handler; }
	void clearKeysDown();
private:
	std::map<int, std::unique_ptr<Command>> keysDown = {};
	std::map<std::string, std::function<std::unique_ptr<Command>()>> handlers = {};
};