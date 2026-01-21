#pragma once
#include "characterObject.hpp"
#include "creatureType.hpp"

enum class CreatureState {
	WALK_LEFT,
	WALK_RIGHT,
	WALK_UP,
	WALK_DOWN,
	IDLE
};

class Creature : public CharacterObject {
public:
	Creature(int64_t id, vec2<float>& pos, std::shared_ptr<CreatureType> creatureType);

	void changeState();

	void process(float deltaTime) override;
private:
	std::shared_ptr<CreatureType> creatureType_;
	CreatureState currentState_ = CreatureState::IDLE;
	float timePassed = 0;
	float timeUntilStateChange = 0;
};