#pragma once
#include "surface.h"
#include <queue>
#include <functional>
#include <set>
#include "container.hpp"
#include "keyboardInput.hpp"
#include "vec2.hpp"
#include "drawDispatcher.hpp"

class Screen : public Container {
public:
	Screen(Tmpl8::Surface* surface) :
		// screens are really just a container the size of the screen arent they? :)
		Container(0, vec2(0.0f), vec2<float>(surface->GetWidth(), surface->GetHeight()), Justification::NONE, vec2(0.0f)), 
		keyboardInput_(), 
		drawDispatcher_() 
	{};

	virtual void process(float deltaTime) override;

	void deleteObject(int64_t id);

	virtual void subscribe() override;
	virtual void unsubscribe() override;

	void pushToQueue(std::function<void()> func) { queue.push(func); }

	void keyDown(int keyCode) { keyboardInput_.keyDown(keyCode); }
	void keyUp(int keyCode) { keyboardInput_.keyUp(keyCode); }
protected:
	KeyboardInput keyboardInput_;
	DrawDispatcher drawDispatcher_;

	void interactionCheck(Object& object);
	std::set<int64_t> alreadyInteracting = {};

	std::queue<std::function<void()>> queue = {};

	vec2<float> objectsCollideWithBounds(Object& object, vec2<float>& velocity);
};