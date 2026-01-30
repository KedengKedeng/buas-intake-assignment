#pragma once
#include "container.hpp"
#include "creatureType.hpp"
#include "text.hpp"
#include "wallet.hpp"

class AnimalShopItem : public Container {
public:
	AnimalShopItem(int64_t id, vec2<float>& pos, vec2<float>& size, std::shared_ptr<CreatureType> type, std::shared_ptr<Wallet> wallet);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	void process(float deltaTime) override;
private:
	Text text_;
	Text priceText_;
	AnimatedSprite animalSprite_;
	std::shared_ptr<Wallet> wallet_;
};