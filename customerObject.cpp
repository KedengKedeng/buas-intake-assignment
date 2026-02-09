#include "customerObject.hpp"
#include "uiSignals.hpp"
#include "interactionSignal.hpp"

CustomerObject::CustomerObject(
	int64_t id, 
	vec2<float> pos, 
	std::shared_ptr<CustomerType> type, 
	std::shared_ptr<Item> neededItem, 
	std::shared_ptr<Wallet> wallet, 
	std::shared_ptr<Inventory> inventory
) :
	CharacterObject(
		id,
		pos,
		vec2<float>(type->idleLeft.getWidth(), type->idleLeft.getHeight()),
		type->idleLeft,
		type->idleRight,
		type->walkLeft,
		type->walkRight,
		false
	),
	itemSprite(neededItem->sprite),
	neededItem_(neededItem),
	wallet_(wallet),
	inventory_(inventory)
{}

void CustomerObject::process(float deltaTime) {
	CharacterObject::process(deltaTime);

	itemSprite.process(deltaTime);
}

void CustomerObject::subscribe() {
	addSubscription(interactionSignal.subscribe([this]() {
		if (isInteracting && inventory_->get(neededItem_->id)) {
			inventory_->remove(neededItem_->id);
			wallet_->addCurrency(neededItem_->value);
		}
	}));

	addSubscription(onInteractionStart.subscribe([this]() {
		drawOnTop.emit(getId(), [this](Tmpl8::Surface& surface, vec2<float> offset) {
			float spriteScale = 1.5f;
			vec2 itemSize = vec2<float>(itemSprite.getWidth(), itemSprite.getHeight()) * spriteScale;

			auto pos = getPos() - vec2(-(getSize().x - itemSize.x) / 2, itemSize.y + 20) + offset;
			surface.Bar(pos - 10, pos + itemSize + 10, 0xffffffff);

			itemSprite.drawScaled(surface, pos.x, pos.y, spriteScale);
		});
	}));

	addSubscription(onInteractionEnd.subscribe([this]() {
		removeDrawOnTop.emit(getId());
	}));
}