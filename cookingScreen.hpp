#pragma once
#include "screen.hpp"
#include "cookingCauldron.hpp"
#include <set>

class CookingScreen : public Screen {
public:
	CookingScreen(Tmpl8::Surface* surface);
	~CookingScreen();

	void process() override;
	void draw(Tmpl8::Surface* surface) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	int64_t cauldronId;
	bool trackSpoonMovement = false;

	std::function<void()> escapePressedUnsub = []() {};
	std::function<void()> cauldronInteractedUnsub = []() {};
	std::function<void()> cauldronInteractionEndedUnsub = []() {};
	std::function<void()> requestMoveUnsub = []() {};
};