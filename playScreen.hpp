#pragma once
#include "screen.hpp"
#include "player.hpp"
#include "playerSignals.hpp"
#include <memory>
#include "wall.hpp"
#include "cauldron.hpp"
#include "itemObject.hpp"
#include "sprite.hpp"

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface) : Screen(surface), player_(Sprite(std::string("rotatingGun"), 1), Tmpl8::vec2(10, 10)) {
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0, 0), Tmpl8::vec2(1, surface->GetHeight())));
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0, 0), Tmpl8::vec2(surface->GetWidth(), 1)));
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0, surface->GetHeight() - 1), Tmpl8::vec2(surface->GetWidth(), 1)));
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(surface->GetWidth() - 1, 0), Tmpl8::vec2(1, surface->GetHeight())));
		objects.push_back(std::make_unique<Cauldron>(Sprite(std::string("cauldron"), 1), Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight() / 2)));
		objects.push_back(std::make_unique<ItemObject>(Tmpl8::vec2(500, 200), std::string("testItem")));

		requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& velocity, Player& player) {
			BoundingBox bounds = player.getBounds();
			Tmpl8::vec2 collides = objectsCollideWithBounds(bounds.at(oldPos), velocity);

			player.move(oldPos + collides);
		});
	};

	void process() override;
	void draw() override;

	Tmpl8::vec2 objectsCollideWithBounds(BoundingBox& bounds, Tmpl8::vec2 velocity);
private:
	Player player_;
	std::vector<std::unique_ptr<Object>> objects = {};
};