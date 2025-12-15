#pragma once
#include "screen.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory, std::shared_ptr<Husbandry> husbandry);
	~PlayScreen();

	void createWorldBounds(Tmpl8::vec2& size);

	void deleteObject(int64_t id);

	void process() override;
	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Player player_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<Husbandry> husbandry_;
};