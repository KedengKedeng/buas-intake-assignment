#include "worldCauldron.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

const float cauldronSpriteScale = 2.5f;
const float cauldronSpriteFrameRate = 0.005f;

WorldCauldron::WorldCauldron(int64_t id, vec2<float> pos, std::shared_ptr<Cauldron> cauldron) :
	Object(id, pos, vec2(0.0f)),
	Collider(),
	Interactable(vec2(-10.0f), vec2(0.0f), false),
	cauldron_(cauldron),
	sprites_(std::vector<AnimatedSprite>({
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{spriteRepository().get(Sprites::EmptyCauldron, cauldronSpriteScale)}), cauldronSpriteFrameRate),
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::FilledCauldron), cauldronSpriteFrameRate, cauldronSpriteScale),
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::EmptyBurningCauldron), cauldronSpriteFrameRate, cauldronSpriteScale),
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::FilledBurningCauldron), cauldronSpriteFrameRate, cauldronSpriteScale)
	}))
{
	addCollider(BoundingBox(vec2(0.0f), vec2(sprites_.getWidth(), sprites_.getHeight())));

	vec2<float> spriteSize(sprites_.getWidth(), sprites_.getHeight());
	interactionBox_.setSize(spriteSize + 10);

	setPos(getPos() - (spriteSize / 2));
}

WorldCauldron::~WorldCauldron() {
	onInteractEnd();
}

void WorldCauldron::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	int spriteNum = cauldron_->getItemCount() != 0;
	if (cauldron_->getTemp() > 200) spriteNum += 2;
	sprites_.setSprite(spriteNum);

	auto pos = getPos() + offset;
	sprites_.draw(surface, pos.x, pos.y);
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