#include "playScreen.hpp"

void PlayScreen::draw() {
	player.draw(surface_);
}

void PlayScreen::process() {
	surface_->Clear(255 << 8);
	player.process();
	draw();
}