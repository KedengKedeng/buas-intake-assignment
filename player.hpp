#pragma once
#include "characterObject.hpp"
#include "template.h"
#include "item.hpp"

class Player : public CharacterObject {
public:
	Player(int64_t id, vec2<float>& pos);

	void subscribe() override;
};