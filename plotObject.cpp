#include "plotObject.hpp"
#include "objectSignals.hpp"
#include "interactionSignal.hpp"
#include "random.hpp"
#include "creature.hpp"
#include "uiSignals.hpp"

PlotObject::PlotObject(
	int64_t id, 
	vec2<float> pos, 
	vec2<float> size, 
	std::shared_ptr<Plot> plot, 
	std::shared_ptr<Inventory> inventory,
	std::shared_ptr<Husbandry> husbandry
) :
	Object(id, pos, size),
	Interactable(vec2(0.0f), size, false),
	Collider(),
	plot_(plot),
	inventory_(inventory),
	husbandry_(husbandry)
{
	addCollider(BoundingBox(vec2(0.0f), vec2(1.0f, size.y - 1)));
	addCollider(BoundingBox(vec2(0.0f), vec2(size.x - 1, 1.0f)));
	addCollider(BoundingBox(vec2(0.0f, size.y - 1), vec2(size.x - 1, 1.0f)));
	addCollider(BoundingBox(vec2(size.x - 1, 0.0f), vec2(1.0f, size.y - 1)));
}

PlotObject::~PlotObject() {
	for (auto id : animalIds) deleteObjectSignal.emit(id);
	removeDrawOnTop.emit(getId());
}

void PlotObject::addAnimal() {
	int64_t id = getRandomNum();
	createObjectSignal.emit(std::make_shared<Creature>(id, getPos() + 1, plot_->getType()));
	animalIds.push_back(id);
	plot_->addCreature();
}

void PlotObject::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	surface->Box(pos, pos + getSize(), 0xff0000ff);
}

void PlotObject::process(float deltaTime) {
	std::shared_ptr<Item> producedItem = plot_->progressProduction(deltaTime / 1000);
	if (producedItem != nullptr) availableForPickup[producedItem]++;
}

void PlotObject::subscribe() {
	addSubscription(interactionSignal.subscribe([this]() {
		if (isInteracting) {
			if (availableForPickup.size() != 0) {
				for (auto& [item, count] : availableForPickup) for (int x = 0; x < count; x++) inventory_->add(item->name);
				availableForPickup.clear();
				return;
			}
			
			std::string typeName = plot_->getType()->name;
			if (husbandry_->get(typeName)) {
				addAnimal();
				husbandry_->remove(typeName);
			}
		}
	}));

	addSubscription(onInteractionStart.subscribe([this]() {
		drawOnTop.emit(getId(), [this](Tmpl8::Surface* surface, vec2<float> offset) {
			if (availableForPickup.size() == 0) return;

			vec2 itemSizes(0.0f);
			for (auto& [item, count] : availableForPickup) itemSizes += vec2<float>(item->sprite.getWidth() + 10, 0.0f);
			itemSizes.y += availableForPickup.begin()->first->sprite.getHeight();

			auto pos = getPos() + (getSize() - itemSizes) / 2 + offset;
			surface->Bar(pos - 10, pos + itemSizes + 10, 0xffffffff);

			for (auto& [item, count] : availableForPickup) {
				item->sprite.draw(surface, pos.x, pos.y);
				pos += vec2<float>(item->sprite.getWidth() + 10, 0.0f);
			}
		});
	}));

	addSubscription(onInteractionEnd.subscribe([this]() {
		removeDrawOnTop.emit(getId());
	}));
}