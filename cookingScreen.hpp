#pragma once
#include "screen.hpp"
#include "cookingCauldron.hpp"
#include <set>

class CookingScreen : public Screen {
public:
	CookingScreen(Tmpl8::Surface* surface);
	~CookingScreen();

	void process() override;
	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	int64_t cauldronId;
	bool trackSpoonMovement = false;
	bool trackBlowerMovement = false;

	void onBlow(float delta) { if (delta > 0) dynamic_cast<CookingCauldron*>(objects_[cauldronId].get())->addTemp(delta); }

	std::function<void()> cauldronInteractedUnsub = []() {};
	std::function<void()> cauldronInteractionEndedUnsub = []() {};
	std::function<void()> blowerInteractedUnsub = []() {};
	std::function<void()> blowerInteractionEndedUnsub = []() {};
	std::function<void()> blowedSignalUnsub = []() {};
	std::function<void()> requestMoveUnsub = []() {};
};