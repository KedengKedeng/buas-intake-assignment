#pragma once
#include "object.hpp"
#include "clickable.hpp"
#include "creatureType.hpp"
#include "text.hpp"
#include "wallet.hpp"
#include "husbandry.hpp"

class AnimalShopItem : public Object, public Clickable {
public:
	AnimalShopItem(
		int64_t id, 
		vec2<float> pos, 
		vec2<float> size, 
		std::shared_ptr<CreatureType> type, 
		std::shared_ptr<Wallet> wallet, 
		std::shared_ptr<Husbandry> husbandry
	);

	void onMouseDown(vec2<float> pos, vec2<float> screenPos) override;

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
	void process(float deltaTime) override;
private:
	std::shared_ptr<CreatureType> type_;
	Text text_;
	Text priceText_;
	mutable AnimatedSprite animalSprite_;

	std::shared_ptr<Wallet> wallet_;
	std::shared_ptr<Husbandry> husbandry_;
};