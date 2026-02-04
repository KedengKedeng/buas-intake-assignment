#pragma once
#include "screen.hpp"
#include "cookingCauldron.hpp"
#include "inventory.hpp"

class CookingScreen : public Screen {
public:
	CookingScreen(Tmpl8::Surface* surface, std::shared_ptr<Cauldron> cauldron, std::shared_ptr<Inventory> inventory);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	std::shared_ptr<Cauldron> cauldron_;

	int64_t cauldronId;
	bool trackSpoonMovement = false;
	bool trackBlowerMovement = false;

	std::shared_ptr<Inventory> inventory_;

	std::function<void()> blowedSignalUnsub = []() {};
};