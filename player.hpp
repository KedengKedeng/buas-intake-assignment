#pragma once
#include "spriteObject.hpp"
#include "template.h"
#include "item.hpp"

class Player : public SpriteObject {
public:
	Player(int64_t id, Tmpl8::vec2& pos);

	void calculateMove();

	void addDelta(Tmpl8::vec2& delta) { delta_ += delta; }

	void process() override;
	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Tmpl8::vec2 velocity = { 6, 6 };
	Tmpl8::vec2 delta_ = { 0, 0 };

	int lookDirection = 0;

	std::function<void()> walkSignalUnsub = []() {};
};