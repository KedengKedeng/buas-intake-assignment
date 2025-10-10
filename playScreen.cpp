#include "playScreen.hpp"

void PlayScreen::draw() {
	for (auto& object : objects)
		object->draw(surface_);
}

void PlayScreen::process() {
	surface_->Clear(255 << 8);

	for (auto& object : objects)
		object->process();

	collisionCheck();

	draw();
}

void PlayScreen::collisionCheck() {
	for (auto& it = objects.begin(); it != objects.end(); it++) {
		for (auto& it2 = objects.begin(); it2 != objects.end(); it2++) {
			if (it == it2) continue;

			BoundingBox bounds = it->get()->getBounds();
			BoundingBox bounds2 = it2->get()->getBounds();

			if (it->get()->getBounds().isInBounds(bounds2))
				bounds.onCollisionStart.emit();
		}
	}
}