#include "creature.hpp"
#include "random.hpp"

Creature::Creature(int64_t id, vec2<float> pos, std::shared_ptr<CreatureType> creatureType) :
	CharacterObject(
		id, 
		pos, 
		vec2<float>(creatureType->idleLeft.getWidth(), creatureType->idleLeft.getHeight()),
		creatureType->idleLeft,
		creatureType->idleRight,
		creatureType->walkLeft,
		creatureType->walkRight,
		false
	), 
	creatureType_(creatureType) 
{
	setVelocity(vec2(60.0f));
}

void Creature::process(float deltaTime) {
	CharacterObject::process(deltaTime);

	if (timePassed > timeUntilStateChange) {
		addDelta(-getDelta());
		changeState();
	}

	timePassed += deltaTime;
}

// let creatures just wander around randomly
void Creature::changeState() {
	CreatureState newState = CreatureState(getRandomNum() % static_cast<int>(CreatureState::LAST));
	timePassed = 0;
	timeUntilStateChange = static_cast<float>(getRandomNum() % 1200 + 300);
	
	switch (newState) {
		case CreatureState::WALK_LEFT:
			addDelta(vec2<int8_t>(-1, 0));
			setLookingDirection(LookingDirections::LEFT);
			break;
		case CreatureState::WALK_RIGHT:
			addDelta(vec2<int8_t>(1, 0));
			setLookingDirection(LookingDirections::RIGHT);
			break;
		case CreatureState::WALK_UP:
			addDelta(vec2<int8_t>(0, -1));
			break;
		case CreatureState::WALK_DOWN:
			addDelta(vec2<int8_t>(0, 1));
			break;
		default:
			break;
	}
}