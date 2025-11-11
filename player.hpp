#pragma once
#include "spriteObject.hpp"
#include "template.h"
#include "item.hpp"

class Player : public SpriteObject {
public:
	Player(int64_t id, Tmpl8::vec2 pos);

	void move(Tmpl8::vec2 newPos);
	void calculateMove();

	void addDelta(Tmpl8::vec2 delta) { delta_ += delta; }

	void setItem(std::shared_ptr<Item> item) { item_ = item; }
	void clearItem() { item_.reset(); }
	std::shared_ptr<Item> getItem() { return item_; }

	void process() override;
	void draw(Tmpl8::Surface* surface) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Tmpl8::vec2 velocity = { 10, 10 };
	Tmpl8::vec2 delta_ = { 0, 0 };

	std::shared_ptr<Item> item_;

	std::function<void()> walkSignalUnsub = []() {};
};