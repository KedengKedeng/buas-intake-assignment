#pragma once

template<typename T>
struct Rect2 {
	Rect2(T x, T y, T width, T height) :
		x(x), y(y), width(width), height(height) {};

	T x;
	T y;
	T width;
	T height;
};