#pragma once
#include "object.hpp"
#include "text.hpp"

class Tooltip : public Object {
public:
	Tooltip(int64_t id, const vec2<float>& pos, std::string& text);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
private:
	Text text_;
};