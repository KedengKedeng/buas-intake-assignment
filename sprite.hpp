#pragma once
#include <string>
#include <memory>
#include "surface.h"
#include "spriteRepository.hpp"

class Sprite {
public:
	Sprite(std::string& name, float scale) : sprite_(spriteRepository.get(name, scale)), scale_(scale), maxFrames_(sprite_->Frames()) {};
	void draw(Tmpl8::Surface* surface, int x, int y) { sprite_->DrawScaled(x, y, getWidth(), getHeight(), surface); }
	void setFrame(unsigned int index);
	unsigned int getFrames() { return sprite_->Frames(); }
	int getWidth() { return static_cast<int>(sprite_->GetWidth() * scale_); }
	int getHeight() { return static_cast<int>(sprite_->GetHeight() * scale_); }
private:
	std::shared_ptr<Tmpl8::Sprite> sprite_;
	float scale_;
	unsigned int maxFrames_;
};