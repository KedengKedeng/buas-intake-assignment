#pragma once
#include "screen.hpp"
#include "cookingCauldron.hpp"
#include <set>

class CookingScreen : public Screen {
public:
	CookingScreen(Tmpl8::Surface* surface);
	~CookingScreen();

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	int64_t cauldronId;
	bool trackSpoonMovement = false;
	bool trackBlowerMovement = false;

	void onBlow(float delta) { if (delta > 0) getObject<CookingCauldron>(cauldronId)->addTemp(delta); }

	std::function<void()> blowedSignalUnsub = []() {};
};