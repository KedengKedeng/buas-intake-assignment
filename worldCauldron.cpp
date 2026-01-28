#include "worldCauldron.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

const float cauldronSpriteScale = 2.5f;
const float cauldronSpriteFrameRate = 0.005f;

WorldCauldron::WorldCauldron(int64_t id, vec2<float>& pos, std::shared_ptr<Cauldron> cauldron) :
	Object(id, pos, vec2(0.0f)),
	Collider(),
	Interactable(vec2(-10.0f), vec2(0.0f), false),
	cauldron_(cauldron),
	sprites_(std::vector<AnimatedSprite>({
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{spriteRepository.get("emptycauldron", cauldronSpriteScale)}), cauldronSpriteFrameRate),
		AnimatedSprite(spriteRepository.getSheet("filledcauldron"), cauldronSpriteFrameRate, cauldronSpriteScale),
		AnimatedSprite(spriteRepository.getSheet("emptyburningcauldron"), cauldronSpriteFrameRate, cauldronSpriteScale),
		AnimatedSprite(spriteRepository.getSheet("filledburningcauldron"), cauldronSpriteFrameRate, cauldronSpriteScale)
	}))
{
	collidingBoxes_.push_back(BoundingBox(vec2(0.0f), vec2(sprites_.getWidth(), sprites_.getHeight())));
	interactionBox_.setSize(vec2(sprites_.getWidth(), sprites_.getHeight()) + 10);
	pos_ = vec2(pos_.x - sprites_.getWidth() / 2, pos_.y - sprites_.getHeight() / 2);
}

WorldCauldron::~WorldCauldron() {
	onInteractEnd();
}

void WorldCauldron::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	int spriteNum = cauldron_->getItemCount() != 0;
	if (cauldron_->getTemp() > 200) spriteNum += 2;
	sprites_.setSprite(spriteNum);

	sprites_.draw(surface, pos_.x + offset.x, pos_.y + offset.y);\
}

void WorldCauldron::process(float deltaTime) {
	sprites_.process(deltaTime);
}

void WorldCauldron::subscribe() {
	addSubscription(interactionSignal.subscribe([this]() {
		if (isInteracting) cauldronInteracted.emit();
	}));

	addSubscription(onInteractionStart.subscribe([this]() {onInteractStart(); }));
	addSubscription(onInteractionEnd.subscribe([this]() {onInteractEnd(); }));
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