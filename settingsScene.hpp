#pragma once
#include "scene.hpp"

class SettingsScene : public Scene {
public:
	SettingsScene(Tmpl8::Surface& surface);

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
};