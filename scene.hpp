#pragma once
#include "surface.h"
#include <queue>
#include <functional>
#include <set>
#include "objectContainer.hpp"
#include "keyboardInput.hpp"
#include "vec2.hpp"
#include "drawDispatcher.hpp"

class Scene : public ObjectContainer {
public:
	Scene(int width, int height) :
		// scenes are really just a container the size of the screen arent they? :)
		ObjectContainer(0, vec2(0.0f), vec2<float>(width, height), Justification::NONE, vec2(0.0f)), 
		keyboardInput_(), 
		drawDispatcher_() 
	{};

	virtual void process(float deltaTime) override;

	virtual void subscribe() override;
	virtual void unsubscribe() override;

	void pushToQueue(std::function<void()> func) { queue.push(std::move(func)); }

	void keyDown(int keyCode) { keyboardInput_.keyDown(keyCode); }
	void keyUp(int keyCode) { keyboardInput_.keyUp(keyCode); }
protected:
	KeyboardInput keyboardInput_;
	DrawDispatcher drawDispatcher_;

	void interactionCheck(const Object& object);
	std::set<int64_t> alreadyInteracting = {};

	std::queue<std::function<void()>> queue = {};

	vec2<float> objectsCollideWithBounds(const Object& object, vec2<float> velocity) const;
};