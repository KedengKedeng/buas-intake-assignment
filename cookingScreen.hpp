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
	CookingCauldron cauldron_;

	std::function<void()> escapePressedUnsub = []() {};
	std::function<void()> requestMoveUnsub = []() {};
};