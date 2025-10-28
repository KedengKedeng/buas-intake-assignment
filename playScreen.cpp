#include "playScreen.hpp"
#include "playerSignals.hpp"
#include <memory>
#include "wall.hpp"
#include "cauldron.hpp"
#include "itemObject.hpp"
#include "sprite.hpp"

PlayScreen::PlayScreen(Tmpl8::Surface* surface) : Screen(surface), player_(Sprite(std::string("rotatingGun"), 1), Tmpl8::vec2(10)) {
	objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0), Tmpl8::vec2(1, surface->GetHeight())));
	objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0), Tmpl8::vec2(surface->GetWidth(), 1)));
	objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0, surface->GetHeight() - 1), Tmpl8::vec2(surface->GetWidth(), 1)));
	objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(surface->GetWidth() - 1, 0), Tmpl8::vec2(1, surface->GetHeight())));
	objects.push_back(std::make_unique<Cauldron>(Sprite(std::string("cauldron"), 1), Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight() / 2)));
	objects.push_back(std::make_unique<ItemObject>(Tmpl8::vec2(500, 200), std::string("testItem")));

	requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& velocity, Player& player) {
		BoundingBox bounds = player.getBounds();
		Tmpl8::vec2 collides = objectsCollideWithBounds(bounds.at(oldPos), velocity);

		Tmpl8::vec2 newPos = oldPos + newPos;

		if (oldPos != newPos) {
			player.move(oldPos + collides);
			interactionCheck(player.getAbsoluteInteractionBounds());
		}
	});
}

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