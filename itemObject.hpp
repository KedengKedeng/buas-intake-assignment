#pragma once
#include "object.hpp"
#include "item.hpp"
#include <cstdio>

class ItemObject : public Object {
public:
	ItemObject(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Item> item);
	~ItemObject();

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
	void process(float deltaTime) override {};

protected:
	void onInteractStart() override;
	void onInteractEnd() override;
private:
	std::shared_ptr<Item> item_;

	// TODO: randomize?
	float drawOffset = 0;
	float minDrawOffset = 0;
	float maxDrawOffset = 20;
	float drawOffsetStep = 0.5f;

	std::function<void()> interactionSignalUnsub = []() {};
};