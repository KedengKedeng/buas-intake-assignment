#include "startScreen.hpp"

void StartScreen::draw() {
	for (auto& button : buttons_)
		button->draw(surface_);
}

void StartScreen::process() {
	surface_->Clear(255);

	draw();
}