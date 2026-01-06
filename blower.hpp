#pragma once
#include "object.hpp"
#include "mouseMoveHandler.hpp"
#include "sprite.hpp"
#include "interactable.hpp"

class Blower : public Object, public Interactable {
public:
	Blower(int64_t id, Tmpl8::vec2& pos);

	void addBlowerPosition(float delta);

	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
	void process(float deltaTime) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	bool inflate = true;
	float blowerPosition = 0;
	MouseMoveHandler mouseMoveHandler;
	std::vector<Sprite> sprites_;
};