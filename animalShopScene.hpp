#pragma once
#include "scene.hpp"
#include "wallet.hpp"
#include "husbandry.hpp"
#include "itemLog.hpp"

class AnimalShopScene : public Scene {
public:
	AnimalShopScene(
		int width, 
		int height, 
		std::shared_ptr<Wallet> wallet, 
		std::shared_ptr<Husbandry> husbandry,
		std::shared_ptr<ItemLog> itemLog
	);
private:
	std::shared_ptr<Wallet> wallet_;
	std::shared_ptr<Husbandry> husbandry_;
	std::shared_ptr<ItemLog> itemLog_;
};