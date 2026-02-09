#pragma once
#include "scene.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"
#include "tilemap.hpp"
#include "cauldron.hpp"
#include "wallet.hpp"

enum class FloorTiles {
	Ground1,
	Ground2,
	Ground3,
	Ground4
};

class PlayScene : public Scene {
public:
	PlayScene(Tmpl8::Surface& surface, std::shared_ptr<Inventory> inventory, std::shared_ptr<Husbandry> husbandry, std::shared_ptr<Cauldron> cauldron, std::shared_ptr<Wallet> wallet);

	void createPlotObjects(std::shared_ptr<Husbandry> husbandry, vec2<float> pos);
	void createWorldBounds(vec2<float> pos, vec2<float> size);

	void process(float deltaTime) override;
	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Tilemap<FloorTiles> floorTiles_;

	Player player_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<Husbandry> husbandry_;
	std::shared_ptr<Wallet> wallet_;
};