#pragma once
#include "object.hpp"
#include "spriteStack.hpp"
#include "collider.hpp"
#include "interactable.hpp"
#include "vec2.hpp"

enum class LookingDirections {
	LEFT,
	RIGHT
};

class CharacterObject : public Object, public Collider, public Interactable {
public:
	CharacterObject(
		int64_t id, 
		vec2<float> pos, 
		vec2<float> size, 
		const AnimatedSprite& idleLeft,
		const AnimatedSprite& idleRight,
		const AnimatedSprite& walkLeft,
		const AnimatedSprite& walkRight,
		bool isInteractor
	);

	void calculateMove();

	void addDelta(vec2<int8_t> delta) { delta_ += delta; }
	vec2<int8_t> getDelta() const { return delta_; }

	void setLookingDirection(LookingDirections lookingDirection) { lookingDirection_ = lookingDirection; }
	LookingDirections getLookingDirection() const { return lookingDirection_; }

	void process(float deltaTime) override;
	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
protected:
	float getTextureWidth() const { return sprites_.getWidth(); }
	float getTextureHeight() const { return sprites_.getHeight(); }
	vec2<float> velocity = { 6, 6 };
private:
	vec2<int8_t> delta_ = { 0, 0 };

	LookingDirections lookingDirection_ = LookingDirections::LEFT;
	mutable SpriteStack sprites_;
};