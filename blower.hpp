#pragma once
#include "object.hpp"
#include "spritesheet.hpp"
#include "vec2.hpp"
#include "clickable.hpp"

class Blower : public Object, public Clickable {
public:
	Blower(int64_t id, vec2<float> pos);

	void addBlowerPosition(float delta);

	void onMouseDown(vec2<float> pos, vec2<float> screenPos) override;
	void onMouseUp(vec2<float> pos, vec2<float> screenPos) override;
	void onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) override;

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	void process(float deltaTime) override;
private:
	bool inflate = true;
	float blowerPosition = 0;
	const std::shared_ptr<SpriteSheet> sprites_;
};