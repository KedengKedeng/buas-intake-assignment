#include "animalShopItem.hpp"
#include "boundingBox.hpp"
#include <format>

AnimalShopItem::AnimalShopItem(
	int64_t id, 
	vec2<float>& pos, vec2<float>& size, 
	std::shared_ptr<CreatureType> type, 
	std::shared_ptr<Wallet> wallet,
	std::shared_ptr<Husbandry> husbandry
) :
	Container(id, pos, size, Justification::HORIZONTAL, vec2(0.0f, 10.0f)),
	Clickable([this]() {
		bool success = wallet_->requestPayment(type_->price);
		if (success) husbandry_->add(type_->name);
	}),
	type_(type),
	text_(type->name, 2, 0xff000000),
	priceText_(std::format("cost: {}", type->price), 2, 0xff000000),
	animalSprite_(type->idleRight),
	wallet_(wallet),
	husbandry_(husbandry)
{
	mouseHandler_.setInteractionCheck([this](vec2<float>& pos) {
		return BoundingBox(getPos(), getSize()).isInBounds(pos);
	});
}

void AnimalShopItem::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	int padding = 20;
	auto pos = getPos() + offset;
	auto size = getSize();
	surface->Bar(pos, pos + size, 0xffffffff);
	surface->Box(pos, pos + size, 0xff000000);

	surface->Bar(pos + 10, pos + vec2(size.y - 10), 0xff000000);
	vec2<float> spriteSize(animalSprite_.getWidth() * 0.75f, animalSprite_.getHeight() * 0.75f);
	auto spritePos = pos + (vec2(size.y) - spriteSize) / 2;
	animalSprite_.drawScaled(surface, spritePos.x, spritePos.y, 0.75f);

	vec2 textSize = vec2<float>(text_.getWidth(), text_.getHeight());
	text_.draw(surface, pos + (size - textSize) / 2);

	vec2 priceTextSize(priceText_.getWidth(), priceText_.getHeight());
	priceText_.draw(surface, pos + size - priceTextSize);

	// grey out the item if it cant be bought
	if (wallet_->getCurrency() < type_->price) surface->Bar(pos, pos + size, 0x50000000);
}

void AnimalShopItem::process(float deltaTime) {
	Container::process(deltaTime);

	animalSprite_.process(deltaTime);
}

void AnimalShopItem::subscribe() {
	Container::subscribe();

	mouseHandler_.subscribe();
	addSubscription([this]() {mouseHandler_.unsubscribe(); });
}