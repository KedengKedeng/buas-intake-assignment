#pragma once
#include "surface.h"

class Screen {
public:
	Screen(Tmpl8::Surface* surface) {
		surface_ = surface;
	};

	virtual void draw() = 0;
	virtual void process() = 0;
protected:
	Tmpl8::Surface* surface_;
};