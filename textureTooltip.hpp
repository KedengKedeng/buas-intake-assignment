#pragma once
#include "object.hpp"
#include "animatedSprite.hpp"

class TextureTooltip : public Object {
public:
	TextureTooltip(int64_t id, const vec2<float>& pos, AnimatedSprite& sprite);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	void process(float deltaTime) override;
private:
	AnimatedSprite sprite_;
};