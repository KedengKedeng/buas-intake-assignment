#pragma once
#include "screen.hpp"
#include "wallet.hpp"
#include "husbandry.hpp"

class AnimalShopScreen : public Screen {
public:
	AnimalShopScreen(Tmpl8::Surface* surface, std::shared_ptr<Wallet> wallet, std::shared_ptr<Husbandry> husbandry);

	void subscribe() override;
private:
	std::shared_ptr<Wallet> wallet_;
	std::shared_ptr<Husbandry> husbandry_;
};