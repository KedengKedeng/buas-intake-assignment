#pragma once
#include "screen.hpp"

class SettingsScreen : public Screen {
public:
	SettingsScreen(Tmpl8::Surface* surface);

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
};