#pragma once
#include "surface.h"
#include <stack>
#include <functional>

class Screen {
public:
	Screen(Tmpl8::Surface* surface) {
		surface_ = surface;
	};

	virtual void draw() = 0;
	virtual void process();
protected:
	Tmpl8::Surface* surface_;
	std::stack<std::function<void()>> queue = {};
};