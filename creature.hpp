#pragma once
#include "characterObject.hpp"
#include "creatureType.hpp"

class Creature : public CharacterObject {
public:
	Creature(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<CreatureType> creatureType);
private:
	std::shared_ptr<CreatureType> creatureType_;
};