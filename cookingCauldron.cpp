#include "cookingCauldron.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

CookingCauldron::CookingCauldron(int64_t id, std::shared_ptr<Cauldron> cauldron) : 
	Object(id, vec2(0.0f), vec2(0.0f)), 
	cauldronFront(spriteRepository().get(Sprites::CauldronCloseupFront, 0.5)),
	cauldronBack(spriteRepository().get(Sprites::CauldronCloseupBack, 0.5)),
	cauldronInside(AnimatedSprite(spriteRepository().getSheet(SpriteSheets::CauldronCloseupFilled), 0.005f, 0.5)),
	fire(AnimatedSprite(spriteRepository().getSheet(SpriteSheets::CauldronCloseupFire), 0.005f, 0.4)),
	cauldron_(cauldron)
{
	setPos(vec2(cauldronFront.getWidth() / 2, cauldronFront.getHeight()));
	setSize(vec2(cauldronFront.getWidth(), cauldronFront.getHeight()));

	auto size = getSize();
	addCollider(BoundingBox(vec2(80.0f), vec2(40.0f, size.y - 80)));
	addCollider(BoundingBox(vec2(size.x - 100, 80.0f), vec2(40.0f, size.y - 80)));
	addCollider(BoundingBox(vec2(80.0f, size.y - 100), vec2(size.x - 140, 1.0f)));

	// the asset has a lot of white space so we need to add an offset
	// to make the bounding box feel a bit better
	interactionBox_.setPos(vec2(120.0f, 80.0f));
	interactionBox_.setSize(vec2(size.x - 220, size.y - 80));
}

void CookingCauldron::drawBack(Tmpl8::Surface* surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	cauldronBack.draw(surface, pos.x, pos.y);

	if (cauldron_->getItemCount() != 0) {
		cauldronInside.draw(
			surface,
			pos.x + (cauldronFront.getWidth() / 2 - cauldronInside.getWidth() / 2),
			pos.y
		);
	};
}

void CookingCauldron::drawFront(Tmpl8::Surface* surface, vec2<float> offset) const {
	auto pos = getPos();
	cauldronFront.draw(surface, pos.x, pos.y);

	fire.draw(
		surface,
		pos.x + (cauldronFront.getWidth() / 2 - fire.getWidth() / 2), 
		// offset the height by the temperature of the cauldron.
		// this gives a little effect where the fire springs up as the cauldron gets hotter.
		pos.y + (cauldronFront.getHeight() - (fire.getHeight() - 20)) + (200 - std::min(cauldron_->getTemp() / 4, 200.0f))
	);
}

void CookingCauldron::process(float deltaTime) {
	cauldronInside.process(deltaTime);
	fire.process(deltaTime);
}

void CookingCauldron::subscribe() {
	addSubscription(onInteractionStart.subscribe([this]() {cauldronInteracted.emit(); }));
	addSubscription(onInteractionEnd.subscribe([this]() {cauldronInteractionEnded.emit(); }));
}