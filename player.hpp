#pragma once
#include "spriteObject.hpp"
#include "template.h"

class Player : public SpriteObject {
public:
	Player(int64_t id, Sprite& sprite, Tmpl8::vec2 pos);

	void move(Tmpl8::vec2 newPos);
	void calculateMove();

	void addDelta(Tmpl8::vec2 delta) { delta_ += delta; }

	void process() override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Tmpl8::vec2 velocity = { 10, 10 };
	Tmpl8::vec2 delta_ = { 0, 0 };

	std::function<void()> walkSignalUnsub;
};