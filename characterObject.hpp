#pragma once
#include "object.hpp"
#include "spriteStack.hpp"

enum class LookingDirections {
	LEFT,
	RIGHT
};

class CharacterObject : public Object {
public:
	CharacterObject(
		int64_t id, 
		Tmpl8::vec2& pos, 
		BoundingBox& boundingBox, 
		ObservableBoundingBox& interactableBoundingBox,
		AnimatedSprite& idleLeft,
		AnimatedSprite& idleRight,
		AnimatedSprite& walkLeft,
		AnimatedSprite& walkRight
	);

	void calculateMove();

	void addDelta(Tmpl8::vec2& delta) { delta_ += delta; }
	Tmpl8::vec2 getDelta() { return delta_; }

	void setLookingDirection(LookingDirections lookingDirection) { lookingDirection_ = lookingDirection; }
	LookingDirections getLookingDirection() { return lookingDirection_; }

	void process(float deltaTime) override;
	void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
protected:
	float getTextureWidth() { return sprites_.getWidth(); }
	float getTextureHeight() { return sprites_.getHeight(); }
private:
	Tmpl8::vec2 velocity = { 6, 6 };
	Tmpl8::vec2 delta_ = { 0, 0 };

	LookingDirections lookingDirection_ = LookingDirections::LEFT;
	SpriteStack sprites_;
};