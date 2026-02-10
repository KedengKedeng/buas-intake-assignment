#include "animalShopItem.hpp"
#include <format>

AnimalShopItem::AnimalShopItem(
	int64_t id, 
	vec2<float> pos, 
	vec2<float> size, 
	std::shared_ptr<CreatureType> type, 
	std::shared_ptr<Wallet> wallet,
	std::shared_ptr<Husbandry> husbandry,
	std::shared_ptr<ItemLog> itemLog
) :
	Object(id, pos, size),
	type_(type),
	text_(type->name, 2, 0xff000000),
	priceText_(std::format("cost: {}", type->price), 2, 0xff000000),
	animalSprite_(type->idleRight),
	wallet_(wallet),
	husbandry_(husbandry),
	itemLog_(itemLog)
{}

void AnimalShopItem::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	int padding = 20;
	auto pos = getPos() + offset;
	auto size = getSize();
	surface.Bar(pos, pos + size, 0xffffffff);
	surface.Box(pos, pos + size, 0xff000000);

	surface.Bar(pos + 10, pos + vec2(size.y - 10), 0xff000000);
	vec2<float> spriteSize(animalSprite_.getWidth() * 0.75f, animalSprite_.getHeight() * 0.75f);
	auto spritePos = pos + (vec2(size.y) - spriteSize) / 2;
	animalSprite_.drawScaled(surface, spritePos.x, spritePos.y, 0.75f);

	vec2 textSize = vec2<float>(text_.getWidth(), text_.getHeight());
	text_.draw(surface, pos + (size - textSize) / 2);

	vec2 priceTextSize(priceText_.getWidth(), priceText_.getHeight());
	priceText_.draw(surface, pos + size - priceTextSize);

	// grey out the item if it cant be bought
	if (wallet_->getCurrency() < type_->price) surface.Bar(pos, pos + size, 0x50000000);
}

void AnimalShopItem::onMouseDown(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseDown(pos, screenPos);

	bool success = wallet_->requestPayment(type_->price);
	if (success) {
		husbandry_->insert(type_->id);
		itemLog_->logItem(type_->producedItem->id);
	}
}

void AnimalShopItem::process(float deltaTime) {
	Object::process(deltaTime);

	animalSprite_.process(deltaTime);
}