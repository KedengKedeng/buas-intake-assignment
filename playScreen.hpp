#pragma once
#include "screen.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"
#include "tilemap.hpp"
#include "cauldron.hpp"

enum class FloorTiles {
	Ground1,
	Ground2,
	Ground3,
	Ground4
};

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory, std::shared_ptr<Husbandry> husbandry, std::shared_ptr<Cauldron> cauldron);

	void createPlotObjects(std::shared_ptr<Husbandry> husbandry, const vec2<float>& pos);
	void createWorldBounds(const vec2<float>& pos, const vec2<float>& size);

	void process(float deltaTime) override;
	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Tilemap<FloorTiles> floorTiles_;

	Player player_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<Husbandry> husbandry_;
};