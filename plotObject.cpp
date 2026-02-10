#include "plotObject.hpp"
#include "objectSignals.hpp"
#include "interactionSignal.hpp"
#include "random.hpp"
#include "creature.hpp"
#include "uiSignals.hpp"

PlotObject::PlotObject(
	int64_t id, 
	vec2<float> pos, 
	vec2<float> size, 
	std::shared_ptr<Plot> plot, 
	std::shared_ptr<Inventory> inventory,
	std::shared_ptr<Husbandry> husbandry
) :
	Object(id, pos, size),
	Interactable(vec2(0.0f), size, false),
	Collider(),
	plot_(plot),
	inventory_(inventory),
	husbandry_(husbandry),
	producedItemSprite(plot->getType()->producedItem->sprite),
	signSprite_(SpriteRepository().get(Sprites::Sign))
{
	addCollider(BoundingBox(vec2(0.0f), vec2(1.0f, size.y - 1)));
	addCollider(BoundingBox(vec2(0.0f), vec2(size.x - 1, 1.0f)));
	addCollider(BoundingBox(vec2(0.0f, size.y - 1), vec2(size.x - 1, 1.0f)));
	addCollider(BoundingBox(vec2(size.x - 1, 0.0f), vec2(1.0f, size.y - 1)));
}

PlotObject::~PlotObject() {
	for (auto id : animalIds) deleteObjectSignal.emit(id);
	removeDrawOnTop.emit(getId());
}

void PlotObject::addAnimal() {
	int64_t id = getRandomNum();
	createObjectSignal.emit(std::make_shared<Creature>(id, getPos() + 1, plot_->getType()));
	animalIds.push_back(id);
	plot_->addCreature();
}

void PlotObject::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	auto size = getSize();
	surface.Box(pos, pos + size, 0xff0000ff);
	//drawColliders(surface, pos);

	float signScale = 3.0f;
	vec2 signSize = vec2(signSprite_.getWidth(), signSprite_.getHeight()) * signScale;
	vec2 signPos = pos + vec2((size.x - signSize.x) / 2, size.y);
	signSprite_.drawScaled(surface, signPos.x, signPos.y, signScale);

	auto creatureType = plot_->getType();
	float creatureScale = 0.35f;
	auto creatureSize = vec2(creatureType->idleRight.getWidth(), creatureType->idleRight.getHeight()) * creatureScale;
	auto creaturePos = signPos + vec2(signSize.x - creatureSize.x, signSize.y / 1.30f - creatureSize.y) / 2;
	creatureType->idleRight.drawScaled(surface, creaturePos.x, creaturePos.y, creatureScale);
}

void PlotObject::process(float deltaTime) {
	auto producedItem = plot_->progressProduction(deltaTime / 1000);
	if (producedItem) availableForPickup++;
	producedItemSprite.process(deltaTime);
}

void PlotObject::subscribe() {
	addSubscription(interactionSignal.subscribe([this]() {
		if (isInteracting) {
			if (availableForPickup) {
				Items itemId = plot_->getType()->producedItem->id;
				for (int x = 0; x < availableForPickup; x++) inventory_->insert(itemId);
				availableForPickup = 0;
				return;
			}
			
			CreatureTypes creatureId = plot_->getType()->id;
			if (husbandry_->get(creatureId)) {
				addAnimal();
				husbandry_->remove(creatureId);
			}
		}
	}));

	addSubscription(onInteractionStart.subscribe([this]() {
		drawOnTop.emit(getId(), [this](Tmpl8::Surface& surface, vec2<float> offset) {
			if (!availableForPickup) return;

			float spriteScale = 1.5f;
			vec2 itemSize = vec2<float>(producedItemSprite.getWidth(), producedItemSprite.getHeight()) * spriteScale;

			auto pos = getPos() + (getSize() - itemSize) / 2 + offset;
			surface.Bar(pos - 10, pos + itemSize + 10, 0xffffffff);

			producedItemSprite.drawScaled(surface, pos.x, pos.y, spriteScale);
		});
	}));

	addSubscription(onInteractionEnd.subscribe([this]() {
		removeDrawOnTop.emit(getId());
	}));
}