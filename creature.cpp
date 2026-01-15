#include "creature.hpp"

Creature::Creature(int64_t id, vec2<float>& pos, std::shared_ptr<CreatureType> creatureType) :
	CharacterObject(
		id, 
		pos, 
		vec2(0.0f),
		creatureType->idleLeft,
		creatureType->idleRight,
		creatureType->walkLeft,
		creatureType->walkRight,
		false
	), creatureType_(creatureType) {}