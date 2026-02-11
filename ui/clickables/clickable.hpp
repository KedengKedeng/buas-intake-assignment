#pragma once

class Clickable {
public:
	Clickable() = default;
	Clickable(bool skipBoundsCheck) : skipBoundsCheck_(skipBoundsCheck) {}
	virtual ~Clickable() = default;

	bool getSkipBoundsCheck() const { return skipBoundsCheck_; }

	bool getMouseDown() const { return mouseDown_; }
	virtual void onMouseDown(vec2<float> pos, vec2<float> screenPos) { mouseDown_ = true; };
	virtual void onMouseUp(vec2<float> pos, vec2<float> screenPos) { mouseDown_ = false; };
	virtual void onMouseMove(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) {};
	virtual void onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) {};
private:
	bool skipBoundsCheck_ = false;
	bool mouseDown_ = false;
};