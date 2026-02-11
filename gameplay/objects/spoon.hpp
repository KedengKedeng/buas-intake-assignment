#pragma once
#include "object.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include "interactable.hpp"
#include "clickable.hpp"

extern vec2<float> spoonVelocity;

class Spoon : public Object, public Collider, public Interactable, public Clickable {
public:
	Spoon(int64_t id, vec2<float> pos);

	void onMouseDown(vec2<float> pos, vec2<float> screenPos) override;
	void onMouseUp(vec2<float> pos, vec2<float> screenPos) override;
	void onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) override;

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
	void process(float deltaTime) override;
private:
	vec2<float> velocity = spoonVelocity;

	const Sprite sprite_;
};