#pragma once
#include "container.hpp"
#include "creatureType.hpp"
#include "text.hpp"
#include "wallet.hpp"
#include "husbandry.hpp"
#include "clickable.hpp"

class AnimalShopItem : public Container, public Clickable {
public:
	AnimalShopItem(
		int64_t id, 
		vec2<float>& pos, 
		vec2<float>& size, 
		std::shared_ptr<CreatureType> type, 
		std::shared_ptr<Wallet> wallet, 
		std::shared_ptr<Husbandry> husbandry
	);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	void process(float deltaTime) override;

	void subscribe() override;
private:
	std::shared_ptr<CreatureType> type_;
	Text text_;
	Text priceText_;
	AnimatedSprite animalSprite_;

	std::shared_ptr<Wallet> wallet_;
	std::shared_ptr<Husbandry> husbandry_;
};