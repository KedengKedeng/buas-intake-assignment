#pragma once
#include "spriteObject.hpp"
#include "mouseMoveHandler.hpp"

class Blower : public SpriteObject {
public:
	Blower(int64_t id, Tmpl8::vec2& pos);
	~Blower();

	void addBlowerPosition(float delta);

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;
	void process() override;

	void subscribe() override;
	void unsubscribe() override;
private:
	bool inflate = true;
	float blowerPosition = 0;
	MouseMoveHandler mouseMoveHandler;
};