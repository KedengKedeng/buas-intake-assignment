#pragma once
#include "cauldron.hpp"
#include "animatedSprite.hpp"

class CookingCauldron : public Object {
public:
	CookingCauldron(int64_t id, std::shared_ptr<Cauldron> cauldron);
	~CookingCauldron();

	void stir(float delta) { cauldron_->stir(delta); }
	void addTemp(float delta) { cauldron_->addTemp(delta); }

	void drawBack(Tmpl8::Surface* surface);
	void drawFront(Tmpl8::Surface* surface);
	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override {};
	void process(float deltaTime) override;
protected:
	void onInteractStart() override;
	void onInteractEnd() override;
private:
	std::shared_ptr<Cauldron> cauldron_;
	Sprite cauldronFront;
	Sprite cauldronBack;
	AnimatedSprite cauldronInside;
	AnimatedSprite fire;
};