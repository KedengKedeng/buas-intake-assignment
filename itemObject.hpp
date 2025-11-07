#pragma once
#include "object.hpp"
#include "itemsRepository.hpp"
#include <cstdio>

class ItemObject : public Object {
public:
	ItemObject(int64_t id, Tmpl8::vec2 pos, std::string& itemName);
	~ItemObject();

	void draw(Tmpl8::Surface* surface);
	void process() override {};

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

	std::function<void()> interactionSignalUnsub;
};