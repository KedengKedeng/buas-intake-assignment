#pragma once
#include "cauldron.hpp"
#include "objectRepository.hpp"
#include "spriteStack.hpp"

class CookingCauldron : public Object {
public:
	CookingCauldron();
	~CookingCauldron();

	void drawBack(Tmpl8::Surface* surface);
	void drawFront(Tmpl8::Surface* surface);
	void draw(Tmpl8::Surface* surface) override {};
private:
	std::shared_ptr<Cauldron> cauldron_;
	Sprite cauldronFront;
	SpriteStack cauldronInside;
	SpriteStack fire;
};