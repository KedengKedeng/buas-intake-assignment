#pragma once
#include "characterObject.hpp"
#include "creatureType.hpp"

class Creature : public CharacterObject {
public:
	Creature(int64_t id, vec2<float>& pos, std::shared_ptr<CreatureType> creatureType);
private:
	std::shared_ptr<CreatureType> creatureType_;
};