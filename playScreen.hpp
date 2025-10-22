#pragma once
#include "screen.hpp"
#include "player.hpp"
#include "playerSignals.hpp"
#include <memory>
#include "wall.hpp"
#include "cauldron.hpp"

static Tmpl8::Sprite rotatingGun(new Tmpl8::Surface("assets/aagun.tga"), 36);

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface) : Screen(surface), player_(rotatingGun, (10, 10)) {
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0, 0), Tmpl8::vec2(1, surface->GetHeight())));
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0, 0), Tmpl8::vec2(surface->GetWidth(), 1)));
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(0, surface->GetHeight() - 1), Tmpl8::vec2(surface->GetWidth(), 1)));
		objects.push_back(std::make_unique<Wall>(Tmpl8::vec2(surface->GetWidth() - 1, 0), Tmpl8::vec2(1, surface->GetHeight())));
		objects.push_back(std::make_unique<Cauldron>(Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight() / 2)));

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