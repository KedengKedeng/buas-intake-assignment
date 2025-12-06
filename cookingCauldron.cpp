#include "cookingCauldron.hpp"
#include "objectSignals.hpp"

CookingCauldron::CookingCauldron(int64_t id, std::shared_ptr<Cauldron> cauldron) 
	: Object(id, Tmpl8::vec2(0), BoundingBox(), ObservableBoundingBox()), 
	cauldronFront(std::string("cauldroncloseupfront"), 0.5), 
	cauldronBack(std::string("cauldroncloseupback"), 0.5),
	cauldronInside(std::vector<Sprite>()),
	fire(std::vector<Sprite>()) ,
	cauldron_(cauldron)
{
	allowCollision = false;
	
	pos_ = Tmpl8::vec2(cauldronFront.getWidth() / 2, cauldronFront.getHeight());
	boundingBox_.setSize(Tmpl8::vec2(cauldronFront.getWidth(), cauldronFront.getHeight()));

	interactionBoundingBox_.setPos(Tmpl8::vec2(120, 80));
	interactionBoundingBox_.setSize(Tmpl8::vec2(cauldronFront.getWidth() - 220, cauldronFront.getHeight() - 80));

	cauldronInside.addSprite(Sprite(std::string("cauldroncloseupfilled"), 0.5));

	fire.addSprite(Sprite(std::string("cauldroncloseupfire"), 0.4));
}

CookingCauldron::~CookingCauldron() {

}

void CookingCauldron::drawBack(Tmpl8::Surface* surface) {
	cauldronBack.draw(surface, pos_.x, pos_.y);

	if (cauldron_->getItemCount() != 0) {
		cauldronInside.draw(surface, Tmpl8::vec2(
			pos_.x + (cauldronFront.getWidth() / 2 - cauldronInside.getWidth() / 2),
			pos_.y
		));
	};
}

void CookingCauldron::drawFront(Tmpl8::Surface* surface) {
	cauldronFront.draw(surface, pos_.x, pos_.y);

	fire.draw(surface, Tmpl8::vec2(
		pos_.x + (cauldronFront.getWidth() / 2 - fire.getWidth() / 2), 
		pos_.y + (cauldronFront.getHeight() - (fire.getHeight() - 20)))
	);
}

void CookingCauldron::onInteractStart() {
	cauldronInteracted.emit();
}

void CookingCauldron::onInteractEnd() {
	cauldronInteractionEnded.emit();
}