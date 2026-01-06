#include "worldCauldron.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

const float cauldronSpriteScale = 2.5f;
const float cauldronSpriteFrameRate = 0.005f;

WorldCauldron::WorldCauldron(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Cauldron> cauldron) :
	Object(id, pos, Tmpl8::vec2(0)),
	Collider(),
	Interactable(Tmpl8::vec2(-10), Tmpl8::vec2(0), false),
	cauldron_(cauldron),
	sprites_(std::vector<AnimatedSprite>({
		AnimatedSprite(std::vector<Sprite>{spriteRepository.get("emptycauldron", cauldronSpriteScale)}, cauldronSpriteFrameRate),
		spriteRepository.getAnimated("filledcauldron", cauldronSpriteFrameRate, cauldronSpriteScale),
		spriteRepository.getAnimated("emptyburningcauldron", cauldronSpriteFrameRate, cauldronSpriteScale),
		spriteRepository.getAnimated("filledburningcauldron", cauldronSpriteFrameRate, cauldronSpriteScale)
	}))
{
	collidingBox_.setSize(Tmpl8::vec2(sprites_.getWidth(), sprites_.getHeight()));
	interactionBox_.setSize(Tmpl8::vec2(sprites_.getWidth(), sprites_.getHeight()) + 10);
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

	unsubscribers.push_back(onInteractionStart.subscribe([this]() {onInteractStart(); }));
	unsubscribers.push_back(onInteractionEnd.subscribe([this]() {onInteractEnd(); }));
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