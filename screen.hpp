#pragma once
#include "surface.h"
#include <queue>
#include <functional>
#include <memory>
#include <map>
#include <set>
#include "random.hpp"
#include "container.hpp"
#include "keyboardInput.hpp"

class Screen : public Container {
public:
	Screen(Tmpl8::Surface* surface)
		// screens are really just a container the size of the screen arent they? :)
		: Container(0, Tmpl8::vec2(0), Tmpl8::vec2(0), Justification::NONE), keyboardInput_() {};

	virtual void process(float deltaTime) override;

	virtual void unsubscribe() override;

	void pushToQueue(std::function<void()> func) { queue.push(func); }

	void keyDown(int keyCode) { keyboardInput_.keyDown(keyCode); }
	void keyUp(int keyCode) { keyboardInput_.keyUp(keyCode); }
protected:
	KeyboardInput keyboardInput_;

	void interactionCheck(ObservableBoundingBox& bounds);
	std::set<int64_t> alreadyInteracting = {};

	std::queue<std::function<void()>> queue = {};

	Tmpl8::vec2 objectsCollideWithBounds(Object& object, Tmpl8::vec2& velocity);
};