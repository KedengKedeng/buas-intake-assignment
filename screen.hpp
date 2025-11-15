#pragma once
#include "surface.h"
#include <queue>
#include <functional>
#include <memory>
#include <map>
#include "random.hpp"
#include "container.hpp"

class Screen : public Container {
public:
	Screen(Tmpl8::Surface* surface)
		: Container(0, Tmpl8::vec2(0), Tmpl8::vec2(0), Justification::NONE){};

	virtual void process();
protected:
	std::queue<std::function<void()>> queue = {};
};