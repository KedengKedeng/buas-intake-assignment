#pragma once
#include "scene.hpp"
#include "wallet.hpp"
#include "husbandry.hpp"

class AnimalShopScene : public Scene {
public:
	AnimalShopScene(Tmpl8::Surface* surface, std::shared_ptr<Wallet> wallet, std::shared_ptr<Husbandry> husbandry);
private:
	std::shared_ptr<Wallet> wallet_;
	std::shared_ptr<Husbandry> husbandry_;
};