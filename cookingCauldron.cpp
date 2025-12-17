#include "cookingCauldron.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

CookingCauldron::CookingCauldron(int64_t id, std::shared_ptr<Cauldron> cauldron) 
	: Object(id, Tmpl8::vec2(0), BoundingBox(), ObservableBoundingBox()), 
	cauldronFront(spriteRepository.get("cauldroncloseupfront"), 0.5), 
	cauldronBack(spriteRepository.get("cauldroncloseupback"), 0.5),
	cauldronInside(Sprite(spriteRepository.get("cauldroncloseupfilled"), 0.5), 0.005f),
	fire(Sprite(spriteRepository.get("cauldroncloseupfire"), 0.4), 0.005f) ,
	cauldron_(cauldron)
{
	allowCollision = false;
	
	pos_ = Tmpl8::vec2(cauldronFront.getWidth() / 2, cauldronFront.getHeight());
	boundingBox_.setSize(Tmpl8::vec2(cauldronFront.getWidth(), cauldronFront.getHeight()));

	// the asset has a lot of white space so we need to add an offset
	// to make the bounding box feel a bit better
	interactionBoundingBox_.setPos(Tmpl8::vec2(120, 80));
	interactionBoundingBox_.setSize(Tmpl8::vec2(cauldronFront.getWidth() - 220, cauldronFront.getHeight() - 80));
}

CookingCauldron::~CookingCauldron() {

}

void CookingCauldron::drawBack(Tmpl8::Surface* surface) {
	cauldronBack.draw(surface, pos_.x, pos_.y);

	if (cauldron_->getItemCount() != 0) {
		cauldronInside.draw(
			surface,
			pos_.x + (cauldronFront.getWidth() / 2 - cauldronInside.getWidth() / 2),
			pos_.y
		);
	};
}

void CookingCauldron::drawFront(Tmpl8::Surface* surface) {
	cauldronFront.draw(surface, pos_.x, pos_.y);

	fire.draw(
		surface,
		pos_.x + (cauldronFront.getWidth() / 2 - fire.getWidth() / 2), 
		// offset the height by the temperature of the cauldron.
		// this gives a little effect where the fire springs up as the cauldron gets hotter.
		pos_.y + (cauldronFront.getHeight() - (fire.getHeight() - 20)) + (200 - std::min(cauldron_->getTemp() / 4, 200.0f))
	);
}

void CookingCauldron::process(float deltaTime) {
	cauldronInside.process(deltaTime);
	fire.process(deltaTime);
}

void CookingCauldron::onInteractStart() {
	cauldronInteracted.emit();
}

void CookingCauldron::onInteractEnd() {
	cauldronInteractionEnded.emit();
}