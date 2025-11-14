#pragma once
#include "surface.h"
#include <queue>
#include <functional>

class Screen {
public:
	Screen(Tmpl8::Surface* surface) {
		surface_ = surface;
	};

	virtual void draw() = 0;
	virtual void process();

	virtual void subscribe() = 0;
	virtual void unsubscribe() = 0;
protected:
	Tmpl8::Surface* surface_;
	std::queue<std::function<void()>> queue = {};
};