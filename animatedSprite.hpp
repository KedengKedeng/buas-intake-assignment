#pragma once
#include "sprite.hpp"
#include "template.h"

class AnimatedSprite {
public:
	AnimatedSprite(const Sprite& sprite, float frameRate);

	void process(float deltaTime);
	void draw(Tmpl8::Surface* surface, float x, float y);
	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale);

	float getWidth() { return sprite_.getWidth(); }
	float getHeight() { return sprite_.getHeight(); }

	float duration();
private:
	Sprite sprite_;

	float frameRate_;
	float time_;
};