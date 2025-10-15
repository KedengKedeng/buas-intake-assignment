#include "playScreen.hpp"

void PlayScreen::draw() {
	player_.draw(surface_);
	for (auto& object : objects)
		object->draw(surface_);
}

void PlayScreen::process() {
	surface_->Clear(255 << 8);

	player_.process();
	for (auto& object : objects)
		object->process();

	draw();
}

bool PlayScreen::objectsCollideWithBounds(BoundingBox& bounds) {
	for (auto& it = objects.begin(); it != objects.end(); it++) {
		bool collides = it->get()->getAbsoluteBounds().isInBounds(bounds);
		if (collides) return true;
	}

	return false;
}