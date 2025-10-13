#pragma once
#include "screen.hpp"
#include "button.hpp"
#include <vector>

class StartScreen : public Screen {
public:
	StartScreen(Tmpl8::Surface* surface): Screen(surface) {
		buttons_.push_back(Button(std::string{ "Start game" }, surface_->GetWidth() / 2 - 30, surface_->GetHeight() / 2 - 10, 60, 20, 2));
	};

	void draw() override;
	void process() override;
private:
	std::vector<Button> buttons_ = {};
};