#include "plotObject.hpp"
#include "objectSignals.hpp"
#include "interactionSignal.hpp"
#include "random.hpp"
#include "creature.hpp"

PlotObject::PlotObject(int64_t id, const vec2<float>& pos, const vec2<float>& size, std::shared_ptr<Plot> plot) :
	Object(id, pos, size),
	Interactable(vec2(0.0f), size, false),
	tooltip_(Tooltip(0, pos, std::string("buy"))),
	plot_(plot)
{
	tooltip_.setPos(pos_ + (size_ - tooltip_.getSize()) / 2);
}

PlotObject::~PlotObject() {
	for (auto id : animalIds) deleteObjectSignal.emit(id);
}

void PlotObject::addAnimal() {
	int64_t id = getRandomNum();
	createObjectSignal.emit(std::make_shared<Creature>(id, pos_, plot_->getType()));
	animalIds.push_back(id);
}

void PlotObject::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Box(pos_ + offset, pos_ + size_ + offset, 0xff);
	if (isInteracting) tooltip_.draw(surface, offset);
}

void PlotObject::subscribe() {
	unsubscribers.push_back(interactionSignal.subscribe([this]() {
		if (isInteracting) addAnimal();
	}));
}