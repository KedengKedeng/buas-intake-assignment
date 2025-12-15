#pragma once
#include "characterObject.hpp"
#include "template.h"
#include "item.hpp"

class Player : public CharacterObject {
public:
	Player(int64_t id, Tmpl8::vec2& pos);

	void subscribe() override;
	void unsubscribe() override;
private:
	std::function<void()> walkSignalUnsub = []() {};
};