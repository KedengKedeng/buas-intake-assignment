#pragma once
#include "screen.hpp"
#include <memory>

class StartScreen : public Screen {
public:
	StartScreen(Tmpl8::Surface* surface);

	void process() override;
};