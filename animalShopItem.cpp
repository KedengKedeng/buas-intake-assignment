#include "animalShopItem.hpp"
#include <format>

AnimalShopItem::AnimalShopItem(int64_t id, vec2<float>& pos, vec2<float>& size, std::shared_ptr<CreatureType> type, std::shared_ptr<Wallet> wallet) :
	Container(id, pos, size, Justification::HORIZONTAL),
	type_(type),
	text_(type->name, 1, 0xff000000),
	priceText_(std::format("cost: {}", type->price), 1, 0xff000000),
	animalSprite_(type->idleRight),
	wallet_(wallet)
{}

void AnimalShopItem::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	int padding = 10;
	vec2 pos = pos_ + offset;
	surface->Bar(pos, pos + size_, 0xffffffff);
	surface->Box(pos, pos + size_, 0xff000000);

	surface->Bar(pos + 10, pos + vec2(size_.y - padding), 0xff000000);
	vec2<float> spriteSize(animalSprite_.getWidth() / 1.5f, animalSprite_.getHeight() / 1.5f);
	animalSprite_.drawScaled(
		surface, 
		pos.x + padding + (size_.y - spriteSize.x) / 2 - padding, 
		pos.y + padding + (size_.y - spriteSize.y) / 2 - padding,
		0.75f
	);

	vec2 textSize = vec2<float>(text_.getWidth(), text_.getHeight());
	text_.draw(surface, pos + (size_ - textSize) / 2);

	vec2 priceTextSize(priceText_.getWidth(), priceText_.getHeight());
	priceText_.draw(surface, pos + size_ - priceTextSize);

	// grey out the item if it cant be bought
	if (wallet_->getCurrency() < type_->price) surface->Bar(pos, pos + size_, 0x30000000);
}

void AnimalShopItem::process(float deltaTime) {
	animalSprite_.process(deltaTime);
}