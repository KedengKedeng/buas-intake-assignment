#pragma once
#include "screen.hpp"
#include "player.hpp"
#include "playerSignals.hpp"
#include <memory>
#include "testWall.hpp"

static Tmpl8::Sprite rotatingGun(new Tmpl8::Surface("assets/aagun.tga"), 36);

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface) : Screen(surface), player_(rotatingGun, 10, 10) {
		objects.push_back(std::make_unique<TestWall>(0, 0, 5, surface->GetHeight()));
		objects.push_back(std::make_unique<TestWall>(0, 0, surface->GetWidth(), 5));
		objects.push_back(std::make_unique<TestWall>(0, surface->GetHeight() - 5, surface->GetWidth(), 5));
		objects.push_back(std::make_unique<TestWall>(surface->GetWidth() - 5, 0, 5, surface->GetHeight()));

		requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& newPos, Player& player) {
			//TODO: Move this stuff to the player class itself?
			BoundingBox bounds = player.getBounds();

			bool collidesX = objectsCollideWithBounds(bounds.at(Tmpl8::vec2(newPos.x, oldPos.y)));
			bool collidesY = objectsCollideWithBounds(bounds.at(Tmpl8::vec2(oldPos.x, newPos.y)));

			if (collidesX) newPos.x = oldPos.x;
			if (collidesY) newPos.y = oldPos.y;

			player.move(newPos);
		});
	};

	void process() override;
	void draw() override;

	bool objectsCollideWithBounds(BoundingBox& bounds);
private:
	Player player_;
	std::vector<std::unique_ptr<Object>> objects = {};
};