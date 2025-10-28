#pragma once
#include "screen.hpp"
#include "player.hpp"

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface);

	void process() override;
	void draw() override;
private:
	Tmpl8::vec2 objectsCollideWithBounds(BoundingBox& bounds, Tmpl8::vec2 velocity);
	void interactionCheck(ObservableBoundingBox& bounds);

	Player player_;
	std::vector<std::unique_ptr<Object>> objects = {};
};