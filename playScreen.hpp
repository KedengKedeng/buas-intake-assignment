#pragma once
#include "screen.hpp"
#include "player.hpp"
#include <memory>
#include "testWall.hpp"

static Tmpl8::Sprite rotatingGun(new Tmpl8::Surface("assets/aagun.tga"), 36);

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface) : Screen(surface) {
		objects.push_back(std::make_unique<Player>(rotatingGun, 10, 10));
		objects.push_back(std::make_unique<TestWall>(100, 100));
	};

	void process() override;
	void draw() override;

	void collisionCheck();
private:
	std::vector<std::unique_ptr<Object>> objects = {};
};