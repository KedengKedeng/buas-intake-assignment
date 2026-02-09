#pragma once
#include "scene.hpp"

class SettingsScene : public Scene {
public:
	SettingsScene(int width, int height);

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
};