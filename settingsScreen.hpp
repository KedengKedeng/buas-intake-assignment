#pragma once
#include "screen.hpp"

class SettingsScreen : public Screen {
public:
	SettingsScreen(Tmpl8::Surface* surface);

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	std::function<void()> escapePressedUnsub = []() {};
};