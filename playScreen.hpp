#pragma once
#include "screen.hpp"
#include "player.hpp"

static Tmpl8::Sprite rotatingGun(new Tmpl8::Surface("assets/aagun.tga"), 36);
static Player player(rotatingGun, 10, 10);

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface) : Screen(surface), player_(player) {};
	void process() override;
	void draw() override;
private:
	Player player_;
};