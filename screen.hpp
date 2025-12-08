#pragma once
#include "surface.h"
#include <queue>
#include <functional>
#include <memory>
#include <map>
#include <set>
#include "random.hpp"
#include "container.hpp"

class Screen : public Container {
public:
	Screen(Tmpl8::Surface* surface)
		// screens are really just a container the size of the screen arent they? :)
		: Container(0, Tmpl8::vec2(0), Tmpl8::vec2(0), Justification::NONE){};

	virtual void process();
protected:
	void interactionCheck(ObservableBoundingBox& bounds);
	std::set<int64_t> alreadyInteracting = {};

	std::queue<std::function<void()>> queue = {};

	Tmpl8::vec2 objectsCollideWithBounds(Object& object, Tmpl8::vec2& velocity);
};