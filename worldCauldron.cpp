#include "worldCauldron.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

const float cauldronSpriteScale = 2.5f;
const float cauldronSpriteFrameRate = 0.005f;

WorldCauldron::WorldCauldron(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Cauldron> cauldron) :
	Object(
		id,
		pos,
		BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(0)),
		ObservableBoundingBox(Tmpl8::vec2(-10), Tmpl8::vec2(0))
	),
	cauldron_(cauldron),
	sprites_(std::vector<AnimatedSprite>({
		AnimatedSprite(Sprite(spriteRepository.get("emptycauldron"), cauldronSpriteScale), cauldronSpriteFrameRate),
		AnimatedSprite(Sprite(spriteRepository.get("filledcauldron"), cauldronSpriteScale), cauldronSpriteFrameRate),
		AnimatedSprite(Sprite(spriteRepository.get("emptyburningcauldron"), cauldronSpriteScale), cauldronSpriteFrameRate),
		AnimatedSprite(Sprite(spriteRepository.get("filledburningcauldron"), cauldronSpriteScale), cauldronSpriteFrameRate)
	}))
{
	boundingBox_.setSize(Tmpl8::vec2(sprites_.getWidth(), sprites_.getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(sprites_.getWidth() + 10, sprites_.getHeight() + 10));
	pos_ = Tmpl8::vec2(pos_.x - sprites_.getWidth() / 2, pos_.y - sprites_.getHeight() / 2);
}

WorldCauldron::~WorldCauldron() {
	onInteractEnd();
}

void WorldCauldron::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	int spriteNum = cauldron_->getItemCount() != 0;
	if (cauldron_->getTemp() > 200) spriteNum += 2;
	sprites_.setSprite(spriteNum);

	sprites_.draw(surface, pos_.x + offset.x, pos_.y + offset.y);
}

void WorldCauldron::process(float deltaTime) {
	sprites_.process(deltaTime);
}

void WorldCauldron::subscribe() {
	Object::subscribe();

	unsubscribers.push_back(interactionSignal.subscribe([this]() {
		if (isInteracting) cauldronInteracted.emit();
	}));
}

void WorldCauldron::onInteractStart() {
	isInteracting = true;

	itemDroppedUnsub = itemDropped.subscribe([this](std::shared_ptr<Item> item) {
		cauldron_->insertItem(item);

		return true;
	});
}

void WorldCauldron::onInteractEnd() {
	isInteracting = false;

	itemDroppedUnsub();
}