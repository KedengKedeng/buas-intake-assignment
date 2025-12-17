#pragma once
#include <string>
#include <memory>
#include "surface.h"

class Sprite {
public:
	Sprite(std::shared_ptr<Tmpl8::Sprite> sprite, float scale) 
		: sprite_(sprite), scale_(scale), maxFrames_(sprite_->Frames()) {};

	void draw(Tmpl8::Surface* surface, float x, float y);

	void drawScaled(Tmpl8::Surface* surface, float x, float y, float scale);

	void setFrame(unsigned int index);
	unsigned int getFrames() { return sprite_->Frames(); }
	float getWidth() { return sprite_->GetWidth() * scale_; }
	float getHeight() { return sprite_->GetHeight() * scale_; }
private:
	std::shared_ptr<Tmpl8::Sprite> sprite_;
	float scale_;
	unsigned int maxFrames_;
};