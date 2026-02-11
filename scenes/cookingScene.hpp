#pragma once
#include "scene.hpp"
#include "inventory.hpp"
#include "cauldron.hpp"

class CookingScene : public Scene {
public:
	CookingScene(int width, int height, std::shared_ptr<Cauldron> cauldron, std::shared_ptr<Inventory> inventory);

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;

	void subscribe() override;
private:
	std::shared_ptr<Cauldron> cauldron_;

	int64_t cauldronId;
	bool trackSpoonMovement = false;
	bool trackBlowerMovement = false;

	std::shared_ptr<Inventory> inventory_;

	std::function<void()> blowedSignalUnsub = []() {};
};