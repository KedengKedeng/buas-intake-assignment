#pragma once
#include "numbers.hpp"

template<Arithmatic T>
class vec2 // adapted from https://github.com/dcow/RayTracer
{
public:
	T x, y;

	vec2() {}
	vec2(T v) : x(v), y(v) {}
	vec2(T x, T y) : x(x), y(y) {}
	template<Arithmatic U>
	vec2(U x, U y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

	vec2<T> operator - () const { return vec2(-x, -y); }

	template<Arithmatic U>
	auto operator + (const vec2<U>& addOperand) const -> vec2<std::common_type_t<T, U>> { return vec2(x + addOperand.x, y + addOperand.y); }

	template<Arithmatic U>
	auto operator + (U operand) const -> vec2<std::common_type_t<T, U>> { return vec2(x + operand, y + operand); }

	template<Arithmatic U>
	vec2<T> operator - (const vec2<U>& operand) const { return vec2(x - operand.x, y - operand.y); }

	template<Arithmatic U>
	auto operator - (U operand) const -> vec2<std::common_type_t<T, U>> { return vec2(x - operand, y - operand); }

	template<Arithmatic U>
	auto operator * (const vec2<U>& operand) const -> vec2<std::common_type_t<T, U>> { return vec2(x * operand.x, y * operand.y); }

	template<Arithmatic U>
	auto operator * (U operand) const -> vec2<std::common_type_t<T, U>> { return vec2(x * operand, y * operand); }

	template<Arithmatic U>
	auto operator / (const vec2<U>& operand) const -> vec2<std::common_type_t<T, U>> { return vec2(x / operand.x, y / operand.y); }

	template<Arithmatic U>
	auto operator / (U operand) const -> vec2<std::common_type_t<T, U>> { return vec2(x / operand, y / operand); }

	template<Arithmatic U>
	void operator -= (const vec2<U>& a) { x -= a.x; y -= a.y; }

	template<Arithmatic U>
	void operator += (const vec2<U>& a) { x += a.x; y += a.y; }

	template<Arithmatic U>
	void operator *= (const vec2<U>& a) { x *= a.x; y *= a.y; }

	template<Arithmatic U>
	void operator *= (U a) { x *= a; y *= a; }

	template<Arithmatic U>
	bool operator != (const vec2<U>& a) const { return x != a.x || y != a.y; }

	template<Arithmatic U>
	const bool operator==(const vec2<U>& o) const { return x == o.x && y == o.y; }

	template<Arithmatic U>
	const bool operator<(const vec2<U>& o) const { return x < o.x || (x == o.x && y < o.y); }

	float length() { return sqrtf(x * x + y * y); }
	float sqrLentgh() { return x * x + y * y; }
	vec2 normalized() { float r = 1.0f / length(); return vec2(x * r, y * r); }
	void normalize() { float r = 1.0f / length(); x *= r; y *= r; }
	static vec2 normalize(vec2 v) { return v.normalized(); }
	float dot(const vec2& operand) const { return x * operand.x + y * operand.y; }
};