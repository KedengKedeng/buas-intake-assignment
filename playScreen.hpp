#pragma once
#include "screen.hpp"
#include "player.hpp"
#include <set>

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface);
	~PlayScreen();

	void deleteObject(int64_t id);

	void process() override;
	void draw() override;
	void insertObject(std::unique_ptr<Object> object);

	void subscribe() override;
	void unsubscribe() override;
private:
	Tmpl8::vec2 objectsCollideWithBounds(BoundingBox& bounds, Tmpl8::vec2 velocity);
	void interactionCheck(ObservableBoundingBox& bounds);
	std::set<int64_t> alreadyInteracting = {};

	Player player_;
	std::map<int64_t, std::unique_ptr<Object>> objects = {};

	std::function<void()> deleteObjectSignalUnsub = []() {};
	std::function<void()> itemPickedUpUnsub = []() {};
	std::function<void()> interactionSignalUnsub = []() {};
	std::function<void()> requestMoveUnsub = []() {};
};