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
	Tmpl8::vec2 collisionVec = velocity;

	for (auto& it = objects.begin(); it != objects.end(); it++) {
		if (!it->get()->isCollisionAllowed()) continue;
		CollisionResult result = bounds.swept(it->get()->getAbsoluteBounds(), velocity);
        if (result.collision) {
            Tmpl8::vec2 allowedMovement(0, 0);

            allowedMovement.x += velocity.x * result.time;
            allowedMovement.y += velocity.y * result.time;

			// Check for remaining times for diagonal movement
            float remainingTime = 1 - result.time;
            if (result.normalX == 0.0f) allowedMovement.x += velocity.x * remainingTime;
            if (result.normalY == 0.0f) allowedMovement.y += velocity.y * remainingTime;
            
			// Compare to collisions beforehand so the minimum collision in a direction is always chosen.
            if (velocity.x >= 0.0f) collisionVec.x = std::min(collisionVec.x, allowedMovement.x);
            else collisionVec.x = std::max(collisionVec.x, allowedMovement.x);

            if (velocity.y >= 0.0f) collisionVec.y = std::min(collisionVec.y, allowedMovement.y);
            else collisionVec.y = std::max(collisionVec.y, allowedMovement.y);
        }
	}

	return collisionVec;
}

void PlayScreen::interactionCheck(ObservableBoundingBox& bounds){

}