#pragma once
#include "screen.hpp"

class SettingsScreen : public Screen {
public:
	SettingsScreen(Tmpl8::Surface* surface);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
};