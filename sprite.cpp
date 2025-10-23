#include "sprite.hpp"

void Sprite::setFrame(unsigned int index) { 
	index = std::min(index, maxFrames_);
	index = std::max(index, unsigned int(0));
	sprite_->SetFrame(index); 
}