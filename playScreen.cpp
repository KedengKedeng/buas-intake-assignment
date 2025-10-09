#include "playScreen.hpp"

void PlayScreen::draw() {
	player.draw(surface_);
}

void PlayScreen::process() {
	player.process();
	surface_->Clear(255 << 8);
	draw();
}