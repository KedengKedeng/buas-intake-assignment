#pragma once
#include "object.hpp"
#include "clickable.hpp"
#include <functional>

class Scrollbar : public Object, public Clickable {
public:
	Scrollbar(
		int64_t id, 
		vec2<float> pos, 
		vec2<float> size, 
		vec2<float> parentSize, 
		std::function<void(vec2<float>)> onDrag
	);
	
	void setParentSize(vec2<float>& size);

	void onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) override;

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
private:
	float getThumbSize() const;

	vec2<float> parentSize_;

	float thumbPos_;
	float thumbSize_;

	std::function<void(vec2<float>)> onDrag_;
};