#pragma once
#include "screen.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"
#include "tilemap.hpp"

enum class FloorTiles {
	Ground1,
	Ground2,
	Ground3,
	Ground4
};

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory, std::shared_ptr<Husbandry> husbandry);
	~PlayScreen();

	void createWorldBounds(const Tmpl8::vec2& pos, const Tmpl8::vec2& size);

	void deleteObject(int64_t id);

	void process(float deltaTime) override;
	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Tilemap<FloorTiles> floorTiles_;

	Player player_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<Husbandry> husbandry_;
};