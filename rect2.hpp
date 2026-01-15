#pragma once
#include "numbers.hpp"

template<Arithmatic T>
struct Rect2 {
	Rect2(T x, T y, T width, T height) :
		x(x), y(y), width(width), height(height) {};

	template<Arithmatic U>
	Rect2(U x, U y, U width, U height) :
		x(static_cast<T>(x)),
		y(static_cast<T>(y)),
		width(static_cast<T>(width)),
		height(static_cast<T>(height))
	{}

	template<Arithmatic U>
	Rect2<T> operator/(const U val) {
		return Rect2<T>(x / val, y / val, width / val, height / val);
	}

	T x;
	T y;
	T width;
	T height;
};