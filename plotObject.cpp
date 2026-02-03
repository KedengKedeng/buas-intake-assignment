#include "plotObject.hpp"
#include "objectSignals.hpp"
#include "interactionSignal.hpp"
#include "random.hpp"
#include "creature.hpp"
#include "uiSignals.hpp"

PlotObject::PlotObject(int64_t id, const vec2<float>& pos, const vec2<float>& size, std::shared_ptr<Plot> plot, std::shared_ptr<Inventory> inventory) :
	Object(id, pos, size),
	Interactable(vec2(0.0f), size, false),
	Collider(),
	tooltip_(std::make_shared<Tooltip>(0, pos, std::string("buy"))),
	plot_(plot),
	inventory_(inventory)
{
	addCollider(BoundingBox(vec2(0.0f), vec2(1.0f, size.y - 1)));
	addCollider(BoundingBox(vec2(0.0f), vec2(size.x - 1, 1.0f)));
	addCollider(BoundingBox(vec2(0.0f, size.y - 1), vec2(size.x - 1, 1.0f)));
	addCollider(BoundingBox(vec2(size.x - 1, 0.0f), vec2(1.0f, size.y - 1)));

	tooltip_->setPos(getPos() + (getSize() - tooltip_->getSize()) / 2);
}

PlotObject::~PlotObject() {
	for (auto id : animalIds) deleteObjectSignal.emit(id);
	removeDrawOnTop.emit(tooltip_->getId());
}

void PlotObject::addAnimal() {
	int64_t id = getRandomNum();
	createObjectSignal.emit(std::make_shared<Creature>(id, getPos() + 1, plot_->getType()));
	animalIds.push_back(id);
	plot_->addCreature();
}

void PlotObject::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
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
				for (auto& item : availableForPickup) for (int x = 0; x < item.second; x++) inventory_->add(item.first->name);
				availableForPickup.clear();
			} else addAnimal();
		}
	}));

	addSubscription(onInteractionStart.subscribe([this]() {
		drawOnTop.emit(tooltip_->getId(), [this](Tmpl8::Surface* surface, const vec2<float>& offset) {tooltip_->draw(surface, offset); });
	}));

	addSubscription(onInteractionEnd.subscribe([this]() {
		removeDrawOnTop.emit(tooltip_->getId());
	}));
}