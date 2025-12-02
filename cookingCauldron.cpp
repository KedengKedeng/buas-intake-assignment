#include "cookingCauldron.hpp"

CookingCauldron::CookingCauldron() 
	: Object(0, Tmpl8::vec2(0), BoundingBox(), ObservableBoundingBox()), 
	cauldronFront(std::string("cauldroncloseupfront"), 0.6), 
	cauldronInside(std::vector<Sprite>()),
	fire(std::vector<Sprite>()) 
{
	cauldron_ = std::dynamic_pointer_cast<Cauldron>(objectRepository.get(std::string("cauldron")));
	
	pos_ = Tmpl8::vec2(cauldronFront.getWidth() / 2, cauldronFront.getHeight());

	cauldronInside.addSprite(Sprite(std::string("cauldroncloseupempty"), 0.6));
	cauldronInside.addSprite(Sprite(std::string("cauldroncloseupfilled"), 0.6));

	fire.addSprite(Sprite(std::string("cauldroncloseupfire"), 0.4));
}

CookingCauldron::~CookingCauldron() {

}

void CookingCauldron::drawBack(Tmpl8::Surface* surface) {

}

void CookingCauldron::drawFront(Tmpl8::Surface* surface) {
	cauldronFront.draw(surface, pos_.x, pos_.y);

	cauldronInside.setSprite(cauldron_->getItemCount() != 0);

	cauldronInside.draw(surface, Tmpl8::vec2(
		pos_.x + (cauldronFront.getWidth() / 2 - cauldronInside.getWidth() / 2),
		pos_.y
	));

	fire.draw(surface, Tmpl8::vec2(
		pos_.x + (cauldronFront.getWidth() / 2 - fire.getWidth() / 2), 
		pos_.y + (cauldronFront.getHeight() - fire.getHeight()))
	);
}