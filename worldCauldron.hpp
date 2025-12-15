#pragma once
#include "spriteObject.hpp"
#include "item.hpp"
#include "cauldron.hpp"
#include <vector>

class WorldCauldron : public SpriteObject {
public:
	WorldCauldron(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Cauldron> cauldron);
	~WorldCauldron();

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	void subscribe() override;
protected:
	void onInteractStart() override;
	void onInteractEnd() override;
private:
	std::shared_ptr<Cauldron> cauldron_;

	std::function<void()> itemDroppedUnsub = []() {};

	bool isInteracting = false;
};