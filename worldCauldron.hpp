#pragma once
#include "object.hpp"
#include "spriteStack.hpp"
#include "item.hpp"
#include "cauldron.hpp"
#include "collider.hpp"
#include <vector>

class WorldCauldron : public Object, public Collider {
public:
	WorldCauldron(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Cauldron> cauldron);
	~WorldCauldron();

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
	void process(float deltaTime) override;

	void subscribe() override;
protected:
	void onInteractStart() override;
	void onInteractEnd() override;
private:
	std::shared_ptr<Cauldron> cauldron_;

	std::function<void()> itemDroppedUnsub = []() {};

	bool isInteracting = false;

	SpriteStack sprites_;
};