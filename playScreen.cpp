#include "playScreen.hpp"
#include "playerSignals.hpp"
#include <memory>
#include "wall.hpp"
#include "cauldron.hpp"
#include "itemObject.hpp"
#include "sprite.hpp"
#include "random.hpp"
#include "objectSignals.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "itemsRepository.hpp"

PlayScreen::PlayScreen(Tmpl8::Surface* surface) : Screen(surface), player_(0, Sprite(std::string("rotatingGun"), 1), Tmpl8::vec2(10)) {
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(0), Tmpl8::vec2(surface->GetWidth(), 1)));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(0, surface->GetHeight() - 1), Tmpl8::vec2(surface->GetWidth(), 1)));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(surface->GetWidth() - 1, 0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<Cauldron>(getRandomNum(), Sprite(std::string("cauldron"), 1), Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight() / 2)));
	insertObject(std::make_unique<ItemObject>(getRandomNum(), Tmpl8::vec2(500, 200), itemRepository.get(std::string("testItem"))));

	deleteObjectSignal.subscribe([this](int64_t id) {
		queue.push([this, id]() {deleteObject(id); });
	});

	itemPickedUp.subscribe([this](std::shared_ptr<Item> item) {
		player_.setItem(item);
	});

	interactionSignal.subscribe([this]() {
		auto item = player_.getItem();

		if (item.get() == nullptr) return;

		if (itemDropped.getListenerCount() == 0) insertObject(std::make_unique<ItemObject>(getRandomNum(), player_.getPos(), item));
		else itemDropped.emit(item);

		player_.clearItem();
	});

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

void PlayScreen::deleteObject(int64_t id) {
	objects.erase(id);
}

void PlayScreen::draw() {
	player_.draw(surface_);
	for (auto& object : objects)
		object.second->draw(surface_);
}

void PlayScreen::process() {
	surface_->Clear(255 << 8);

	player_.process();
	for (auto& object : objects)
		object.second->process();

	Screen::process();
	draw();
}

void PlayScreen::insertObject(std::unique_ptr<Object> object) {
	int64_t id = object->getId();
	objects[id] = std::move(object);
}

Tmpl8::vec2 PlayScreen::objectsCollideWithBounds(BoundingBox& bounds, Tmpl8::vec2 velocity) {
	Tmpl8::vec2 collisionVec = velocity;

	for (auto& it = objects.begin(); it != objects.end(); it++) {
		auto object = it->second.get();
		if (!object->isCollisionAllowed()) continue;

		CollisionResult result = bounds.swept(object->getAbsoluteBounds(), velocity);
        if (result.collision) {
            Tmpl8::vec2 allowedMovement(0, 0);

            allowedMovement.x += velocity.x * result.time;
            allowedMovement.y += velocity.y * result.time;

			// Check for remaining times in case of diagonal movement.
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
	for (auto& it = objects.begin(); it != objects.end(); it++) {
		auto object = it->second.get();
		if (!object->isInteractionAllowed()) continue;

		ObservableBoundingBox& objectBounds = object->getInteractionBounds();
		bool result = bounds.isInBounds(object->getAbsoluteInteractionBounds());

		bool foundInteractingObject = alreadyInteracting.find(it->first) != alreadyInteracting.end();
		if (result && !foundInteractingObject) {
			alreadyInteracting.insert(it->first);
			objectBounds.onIntersectStart.emit();
		}

		if (!result && foundInteractingObject) {
			alreadyInteracting.erase(it->first);
			objectBounds.onIntersectEnd.emit();
		}
	}
}