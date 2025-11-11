#pragma once
#include "spriteObject.hpp"
#include "item.hpp"
#include <vector>

class Cauldron : public SpriteObject {
public:
	Cauldron(int64_t id, Tmpl8::vec2 pos);
	~Cauldron();

	void onInteractStart() override;
	void onInteractEnd() override;
private:
	std::vector<std::shared_ptr<Item>> items_ = {};

	std::function<void()> itemDroppedUnsub = []() {};
};