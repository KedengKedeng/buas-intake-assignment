#pragma once

template<typename T>
struct Rect2 {
	Rect2(T x, T y, T width, T height) :
		x(x), y(y), width(width), height(height) {};

	Rect2<T> operator/(const T val) {
		return Rect2<T>(x / val, y / val, width / val, height / val);
	}

	T x;
	T y;
	T width;
	T height;
};