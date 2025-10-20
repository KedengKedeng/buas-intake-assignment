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

Tmpl8::vec2 PlayScreen::objectsCollideWithBounds(BoundingBox& bounds, Tmpl8::vec2 velocity) {
	Tmpl8::vec2 collisionVec(1, 1);

	for (auto& it = objects.begin(); it != objects.end(); it++) {
		Tmpl8::vec2 collides = bounds.swept(it->get()->getAbsoluteBounds(), velocity);
		if (collides.x != 1.0f) collisionVec.x = collides.x;
		if (collides.y != 1.0f) collisionVec.y = collides.y;
	}

	return collisionVec;
}