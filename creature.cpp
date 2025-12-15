#include "creature.hpp"

Creature::Creature(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<CreatureType> creatureType) :
	CharacterObject(
		id, 
		pos, 
		BoundingBox(),
		ObservableBoundingBox(),
		creatureType->idleLeft,
		creatureType->idleRight,
		creatureType->walkLeft,
		creatureType->walkRight
	), creatureType_(creatureType) { 
	allowInteractor = false;
}