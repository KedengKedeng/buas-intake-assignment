#pragma once
#include "screen.hpp"
#include "player.hpp"
#include <set>

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface);

	void deleteObject(int64_t id);

	void process() override;
	void draw() override;
	void insertObject(std::unique_ptr<Object> object);
private:
	Tmpl8::vec2 objectsCollideWithBounds(BoundingBox& bounds, Tmpl8::vec2 velocity);
	void interactionCheck(ObservableBoundingBox& bounds);
	std::set<int> alreadyInteracting = {};

	Player player_;
	std::map<int, std::unique_ptr<Object>> objects = {};
};